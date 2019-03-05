#define SENSOR_1_INPUT A1
#define THRESHOLD_INPUT 5
#define LED_OUTPUT 2

int INITIAL_VALUE = 0;
int SENSOR_1_INITIAL_VALUE = INITIAL_VALUE;
int THRESHOLD = 255;
int ALERT = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(SENSOR_1_INPUT,INPUT);
  int SENSOR_1_INITIAL_VALUE = analogRead(SENSOR_1_INPUT);
}

void loop(){
    Serial.println();
    int sensor1Value = abs(SENSOR_1_INITIAL_VALUE - analogRead(SENSOR_1_INPUT));

    Serial.println(THRESHOLD);
    Serial.println(analogRead(SENSOR_1_INPUT));
   
   if (sensor1Value > THRESHOLD){
     digitalWrite(LED_OUTPUT,HIGH);
        ALERT = 0;
     }
     else {
       digitalWrite(LED_OUTPUT,LOW);
         ALERT = ALERT + 1;
    }
    delay (500);
  }
  
  
