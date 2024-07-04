#include<Ultrasonic.h>

#define SENSOR A0 
#define LED 7


void setup() {  

  //pinMode(SENSOR,OUTPUT);
  Serial.begin(9600);

}

void loop() {

  int sound = analogRead(SENSOR);
  Serial.println(sound);
  
  if(sound>10)
  {
    digitalWrite(LED,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(LED,LOW);
  }
  
}

