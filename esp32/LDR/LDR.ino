#define LDR 34
#define LED 17

void setup() {  
  Serial.begin(9600);  // Corrected baud rate
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
}

void loop() {
  int data = analogRead(LDR);
  Serial.print("Light Sensor value : ");
  Serial.println(data);
  
  if (data < 180) 
  {
    digitalWrite(LED, HIGH);
    //Serial.println("On");
  }
  else 
  {
    digitalWrite(LED, LOW);
    //Serial.println("Off");
  }

  delay(50);
}

