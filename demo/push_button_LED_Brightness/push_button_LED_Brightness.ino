int cnt = 0;
int pin = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8,INPUT_PULLUP);
  pinMode(pin,OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  
  int a = digitalRead(8);
  if(a == 0)
  {
    cnt++;
  }

  if(cnt == 1)
  {
    analogWrite(pin, 100);
  }
  else if(cnt == 2)
  {
    analogWrite(pin, 180);
  }
  else if(cnt == 3)
  {
    analogWrite(pin, 255);
  }
  else
  {
    analogWrite(pin, 0);
    cnt = 0;
  }

  delay(300);
  Serial.println(cnt);

}
