#define RED 11                    /* Pin 11 is Used as Red Signal */
#define YELLOW 13                 /* Pin 13 is Used as YELLOW Signal */
#define GREEN 12                  /* Pin 12 is Used as GREEN Signal */
#define CAR 6                     /* Pin 6 is Used as CAR Signal */
#define DELAY_TIME 10000 


void trafic_light(int,int);


void setup() {  


  Serial.begin(9600);

  pinMode(RED,OUTPUT);                    /* Pin 11 is Used For Output */
  pinMode(YELLOW,OUTPUT);                 /* Pin 13 is Used For Output */
  pinMode(GREEN,OUTPUT);                  /* Pin 12 is Used For Output */
  //pinMode(CAR,OUTPUT);                    /* Pin 7 is Used For Output */

}

void loop() {

  trafic_light(GREEN,200);

  trafic_light(YELLOW,75);

  trafic_light(RED,0);
}

void trafic_light(int pin_number,int car_speed)
{
  digitalWrite(pin_number,HIGH);
  analogWrite(CAR,car_speed);
  delay(DELAY_TIME);
  digitalWrite(pin_number,LOW);
}

