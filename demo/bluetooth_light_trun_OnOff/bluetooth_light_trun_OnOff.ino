#define BULB 8

String s;

void setup() {

  Serial.begin(9600);
  pinMode(BULB,OUTPUT);
  digitalWrite(BULB,LOW);
}

void loop() {

  if(Serial.available())
  {
    s = Serial.readString();
    delay(2);
    Serial.println(s);

    if(s=="turn on the light" || s=="turn on the lights" || s=="light chalu kar" || s=="on" || s=="lights on" || s=="light on" || s=="turn the lights on" || s=="turn the light on" || s=="night chalu kar" || s=="turn on flights" || s=="turn on lights" || s=="turn on flight" || s=="turn on light" || s=="light circuit" || s=="like")
    {
      digitalWrite(BULB,HIGH);
    }
    else if(s=="turn off the light" || s=="turn off the lights" || s=="light band kar" || s=="off" || s=="lights off" || s=="light off" || s=="light bankar" || s=="light bank" || s=="turn the lights off" || s=="turn the light off" || s=="night bankar" || s=="night band kar" || s=="night bank" || s=="light bank" || s=="light wonder car" || s=="add bankar" || s=="light banquet" || s=="turn off flight" || s=="turn off light" || s=="turn off flights" || s=="turn off lights" || s=="turn off night")
    {
      digitalWrite(BULB,LOW);
    }







    
  }
}