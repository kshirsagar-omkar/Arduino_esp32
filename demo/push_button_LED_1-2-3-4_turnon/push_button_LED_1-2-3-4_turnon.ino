int cnt = 0;
int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
int LED4 = 5;
int Push_Button = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Push_Button,INPUT_PULLUP);

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  
  int a = digitalRead(Push_Button);
  if(a == 0)
  {
    cnt++;
  }

  switch(cnt)
  {
    case 1:
            digitalWrite(LED1,HIGH);
            break;
    case 2:
            digitalWrite(LED2,HIGH);
            break;
    case 3:
            digitalWrite(LED3,HIGH);
            break;
    case 4:
            digitalWrite(LED4,HIGH);
            break;
    default :
            digitalWrite(LED1,LOW);
            digitalWrite(LED2,LOW);
            digitalWrite(LED3,LOW);
            digitalWrite(LED4,LOW);
            cnt = 0;
  }


  delay(125);
  Serial.println(cnt);

}
