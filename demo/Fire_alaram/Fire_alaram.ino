#define PIN A0
#define BUZZER 8

void setup() {
  
  pinMode(PIN,INPUT);
  pinMode(BUZZER,OUTPUT);
  Serial.begin(9600);

}

void loop() {

  int a = digitalRead(PIN);
  Serial.println(a);
  if(a==0) digitalWrite(BUZZER,HIGH);
  else digitalWrite(BUZZER,LOW);

  delay(80);
}

