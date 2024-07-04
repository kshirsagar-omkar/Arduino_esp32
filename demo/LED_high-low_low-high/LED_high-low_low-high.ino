int cnt = 0;
int pin = 5;
int i = 0;
int Push_Button = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5,OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  
  for(i=0; i<4; i++)
  {
    if(i==0)
    {
      analogWrite(pin,0);
    }
    else if(i==1)
    {
      analogWrite(pin,100);
    }
    else if(i==2)
    {
      analogWrite(pin,180);
    }
    else if(i==3)
    {
      analogWrite(pin,255);
    }
    delay(150);
  }
  for(i=0; i<3; i++)
  {
    if(i==0)
    {
      analogWrite(pin,255);
    }
    else if(i==1)
    {
      analogWrite(pin,180);
    }
    else if(i==2)
    {
      analogWrite(pin,100);
    }
    delay(150);
  }
}
