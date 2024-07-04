#define BULB 12
#define R1 8
#define R2 9
#define R3 10



String s;

void setup() {

  Serial.begin(9600);

  pinMode(BULB,OUTPUT);
  digitalWrite(BULB,HIGH);

  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(R3,OUTPUT);
  digitalWrite(R1,HIGH);
  digitalWrite(R2,HIGH);
  digitalWrite(R3,HIGH);
}

void loop() {

  if(Serial.available())
  {
    s = Serial.readString();
    delay(2);
    Serial.println(s);

    if(s=="turn on the light" || s=="turn on the lights" || s=="light chalu kar" || s=="on" || s=="lights on" || s=="light on" || s=="turn the lights on" || s=="turn the light on" || s=="night chalu kar" || s=="turn on flights" || s=="turn on lights" || s=="turn on flight" || s=="turn on light" || s=="light circuit" || s=="like")
    {
      digitalWrite(R1,LOW);
    }
    else if(s=="turn flight on" || s=="turn light on" || s=="" || s=="" || s=="" || s=="")
    {
      digitalWrite(R1,LOW);
    }
    else if(s=="turn off the light" || s=="turn off the lights" || s=="light band kar" || s=="off" || s=="lights off" || s=="light off" || s=="light bankar" || s=="light bank" || s=="turn the lights off" || s=="turn the light off" || s=="night bankar" || s=="night band kar" || s=="night bank" || s=="light bank" || s=="light wonder car" || s=="add bankar" || s=="light banquet" || s=="turn off flight" || s=="turn off light" || s=="turn off flights" || s=="turn off lights" || s=="turn off night")
    {
      digitalWrite(R1,HIGH);
    }
    else if(s=="TV on" || s=="turn on tv" || s=="turn the tv on" || s=="turn on the tv" || s=="tv on" || s=="tv chalu kar" || s=="turn tv on" || s=="" )
    {
      digitalWrite(R2,LOW);
    }
    else if(s=="TV off" || s=="turn off tv" || s=="turn the tv off" || s=="turn off the tv" || s=="tv off" || s=="tv off" || s=="tv band kar" || s=="tv bankar" || s=="turn tv off")
    {
      digitalWrite(R2,HIGH);
    }
    else if(s=="charger on" || s=="turn the charger on" || s=="turn on the charger" || s=="kajal chalu kar" || s=="4000 chalu kar" || s=="charger chalu kar" || s=="" || s=="" || s=="" || s=="" || s=="" || s=="" || s=="" || s=="" || s=="")
    {
      digitalWrite(R3,LOW);
    }
    else if(s=="charger off" || s=="turn the charger off" || s=="turn off the charger" || s=="kajal band kar" || s=="4000 band kar" || s=="charger band kar" || s=="charger bankar" || s=="" || s=="" || s=="" || s=="" || s=="" || s=="" || s=="" || s=="")
    {
      digitalWrite(R3,HIGH);
    }

    else if(s=="or not" || s=="on all" || s=="shakeela chalu kar" || s=="sagar taluk" || s=="sabar taluka" || s=="sagar chalu kar" || s=="sagara chalu kar" || s=="sagala chalu kr" || s=="sagada chalu kr" || s=="turn on all" || s=="turn all on" || s=="" || s=="" )
    {
      digitalWrite(R1,LOW);
      digitalWrite(R2,LOW);
      digitalWrite(R3,LOW);
    }
    else if(s=="turn all off" || s=="of all" || s=="sawla band kar" || s=="shakeela band kar" || s=="sagar bandh kar" || s=="sagar band kar" || s=="sagara band kar" || s=="sagara bankar" || s=="servo band kar" || s=="sarva band kar" || s=="delhi kabootar baba" || s=="bijli ka bill tera baap bharega" || s=="bijli ka bill tera baap bete ka" || s=="bijli ka bill kharab hai" || s=="bijli ka bill tera baap beta" || s=="" ||s=="" )
    {
      digitalWrite(R1,HIGH);
      digitalWrite(R2,HIGH);
      digitalWrite(R3,HIGH);
    }
    else if(s=="delhi ka bill tera baap bharega" || s=="bijli ka bill darbhanga" || s=="bijli ka bill tera baba" || s=="bijli ka bill tera baap padega" || s=="bijli ka bill tera baap bada na" || s=="" || s=="" || s=="" || s=="" || s=="" || s=="")
    {
      digitalWrite(R1,HIGH);
      digitalWrite(R2,HIGH);
      digitalWrite(R3,HIGH);
    }

    
  }
}