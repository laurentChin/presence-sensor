#define CAPTEUR_SUR_A 4 // broche détection
#define CAPTEUR_SUR_B 3
#define CAPTEUR_SUR_C 2 
#define CAPTEUR_SUR_D 1
#define CAPTEUR_SUR_E 0

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int valini1 = 0;
int valini2 = 0;
int valini3 = 0;
int valini4 = 0;
int valini5 = 0;
int seuil = 150;
int alerte = 0;

bool switch_on = false;

void setup()
{
  Serial.begin(9600);
  calibration();
  pinMode(13,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,INPUT);
  pinMode(3,OUTPUT);
}
  int calibration(){
    int valini1 = analogRead(CAPTEUR_SUR_A);
    int valini2 = analogRead(CAPTEUR_SUR_B);
    int valini3 = analogRead(CAPTEUR_SUR_C);
    int valini4 = analogRead(CAPTEUR_SUR_D);
    int valini5 = analogRead(CAPTEUR_SUR_E);
    }

void loop(){
 
    seuil = analogRead(A5);
    int val1 = abs(valini1 - analogRead(CAPTEUR_SUR_A));
    int val2 = abs(valini2 - analogRead(CAPTEUR_SUR_B));
    int val3 = abs(valini3 - analogRead(CAPTEUR_SUR_C));
    int val4 = abs(valini4 - analogRead(CAPTEUR_SUR_D));
    int val5 = abs(valini5 - analogRead(CAPTEUR_SUR_E));
    
        Serial.print(seuil);
        Serial.println();    
        Serial.print(val1);
        Serial.print(" , ");
        Serial.print(val2);
        Serial.print(" , ");
        Serial.print(val3);
        Serial.print(" , ");
        Serial.print(val4);
        Serial.print(" , ");
        Serial.println(val5);
   // Visual alert
   if ((val1 > seuil) || (val2>seuil) || (val3>seuil) || (val4>seuil) || (val5>seuil)){
     digitalWrite(3,HIGH);
        alerte = 0;
     }
     else {
       digitalWrite(3,LOW);
         alerte = alerte + 1;
    }
    Serial.println(alerte);
    // Sound alert
    if(alerte > 10){
      digitalWrite(7,HIGH);
      Serial.println("Alarme");
    } else {
      Serial.println("Stop Alarme");
      digitalWrite(7,LOW);
    }
    delay (1000);
  }
  
  
