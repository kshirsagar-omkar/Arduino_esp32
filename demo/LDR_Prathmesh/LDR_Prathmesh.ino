// Define the pin where the Light Dependent Resistor (LDR) is connected
int ldrPin = A0;  // Analog pin A0 is used to read the LDR value

// Define the pin where the LED is connected
int led = 7;  // Digital pin 7 is used to control the LED

// Define the threshold value to decide when the LED should turn ON or OFF
int threshold = 60;  // If the LDR reading is below this value, LED will turn ON

// The setup() function runs once when the Arduino starts or resets
void setup()
{
  // Initialize serial communication at a baud rate of 9600
  Serial.begin(9600);
  
  // Set the LED pin as an OUTPUT because we want to control it
  pinMode(led, OUTPUT);
}

// The loop() function runs continuously after setup()
void loop()
{
  // Read the analog value from the LDR sensor
  int data = analogRead(ldrPin);  // LDR gives a value between 0 and 1023
  
  // Print an empty line for better readability in the Serial Monitor
  Serial.println("");

  // Display a message in the Serial Monitor
  Serial.print("Light Sensor ");  // Print static text
  Serial.print("Value = ");       // Print the label
  Serial.print(data);             // Print the actual LDR value

  // Check if the LDR value is below the threshold
  if (data <= threshold)
  {
    // If it's dark, turn ON the LED
    digitalWrite(led, HIGH);
  }
  else
  {
    // If there is enough light, turn OFF the LED
    digitalWrite(led, LOW);
  }
  
  // Add a small delay to stabilize readings (optional)
  delay(100);  // Wait for 100 milliseconds before next reading
}
