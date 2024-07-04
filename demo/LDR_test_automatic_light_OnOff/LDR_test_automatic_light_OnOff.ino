#define LDR A0
#define LED 7

void setup() {  

  Serial.begin(9600);
  pinMode(LED,OUTPUT);

}

void loop() {

  int data = analogRead(LDR);
  Serial.print("Light Sensor value : ");
  Serial.println(data);
  
  if(data <=80)
  {
    digitalWrite(LED,HIGH);
  }
  else
  {
    digitalWrite(LED,LOW);
  }

  delay(200);
  
}