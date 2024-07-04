#include<Ultrasonic.h>

#define BUZZER 6

//FUNCTION DECLARATION or FUNCTION PROTOTYPE

void buzzer_play(unsigned int, unsigned int);

void disp_distance();



Ultrasonic sensor(12,13);//initialisation class HCSR04 (trig pin , echo pin)

void setup() {  

  Serial.begin(9600);
  pinMode(BUZZER,OUTPUT);
}

void loop() {

  disp_distance();

  if((sensor.read())>30)
  {
    digitalWrite(BUZZER,LOW);
    disp_distance();
    delay(500);
  }


    while((sensor.read())>20 && (sensor.read())<=30 )
    {
      digitalWrite(BUZZER,HIGH);
      disp_distance();
      delay(500);

      digitalWrite(BUZZER,LOW);
      disp_distance();
      delay(1000);
    }

    while((sensor.read())>10 && (sensor.read())<=20 )
    {
      digitalWrite(BUZZER,HIGH);
      disp_distance();
      delay(500);
  
      digitalWrite(BUZZER,LOW);
      disp_distance();
      delay(500);
    }

    while((sensor.read())>5 && (sensor.read())<=10 )
    {
      digitalWrite(BUZZER,HIGH);
      disp_distance();
      delay(200);
  
      digitalWrite(BUZZER,LOW);
      disp_distance();
      delay(200);
    }

    while((sensor.read())<=5 )
    {
      digitalWrite(BUZZER,HIGH);
      disp_distance();
    }
  
}


void disp_distance()
{
  Serial.print("Distance in CM : ");
  Serial.println(sensor.read());
}

/*
void buzzer_play(unsigned int pin_number, unsigned int delayTime)
{



}*/
