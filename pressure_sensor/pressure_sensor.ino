#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

#include "env.h" 
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char serverAddress[] = SERVER_ADDRESS;
WiFiClient wifi;
HttpClient httpClient = HttpClient(wifi, serverAddress, 9090);

#define LED_1_OUTPUT 2
#define LED_2_OUTPUT 3

#define THRESHOLD_INPUT 5

int INITIAL_VALUE = 0;
char sensorInputList[] = {A1, A2};
int ledInputList[] = {2,3};
int initialValues[] = {INITIAL_VALUE, INITIAL_VALUE};
int TOLERANCE_INPUT = A0;
int TOLERANCE = 400;
int ALERT = 0;

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < sizeof(sensorInputList); i++) {
    pinMode(sensorInputList[i],INPUT);
    pinMode(ledInputList[i],OUTPUT);
    initialValues[i] = analogRead(sensorInputList[i]);
  }

  pinMode(TOLERANCE_INPUT, INPUT);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

   // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
}

void loop(){
    Serial.println();

    int length = sizeof(sensorInputList)/sizeof(sensorInputList[0]);
    int tolerance = analogRead(TOLERANCE_INPUT);

    String postData = "{ \"tolerance\": "+ String(tolerance) +", \"strips\": [";

    for (int i = 0; i < length; i = i+1) {
      int value = analogRead(sensorInputList[i]);
      if (abs(initialValues[i] - value) < tolerance) {
        digitalWrite(ledInputList[i], HIGH);
        ALERT = ALERT + 1;
      } else {
        digitalWrite(ledInputList[i], LOW);
        ALERT = 0;
      }

      postData = postData + "{\"position\": " + String(i) + ", \"value\": " + String(abs(value)) + "}";

      if (i < length - 1) {
        postData = postData + ", ";
      }
    }

    postData = postData + "]}";

    httpClient.beginRequest();
    httpClient.post("/data");
    httpClient.sendHeader("Content-Type", "application/json");
    httpClient.sendHeader("Content-Length", postData.length());
    httpClient.beginBody();
    httpClient.print(postData);
    httpClient.endRequest();
    
    delay (500);
  }
  
  
