void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, INPUT_PULLUP);
  pinMode(13,OUTPUT);
}



void loop() {
  // put your main code here, to run repeatedly:
  int a = digitalRead(8);
  Serial.println(a);

  a ? digitalWrite(13,LOW) : digitalWrite(13,HIGH);

/*
  if(a==1)
  {
    digitalWrite(13,LOW);
  }
  else
  {
    digitalWrite(13,HIGH);
  }
*/
}