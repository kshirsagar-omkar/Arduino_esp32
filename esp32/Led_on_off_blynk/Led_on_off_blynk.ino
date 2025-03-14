/*
  Project: ESP32 Blynk Control
  Description: This sketch connects the ESP32 to WiFi and the Blynk Cloud to control a device (Relay)
               connected to GPIO 23. You can toggle the device ON/OFF via a Button widget in the Blynk app.
  
  Hardware Setup:
  - ESP32 module (WROOM-32)
  - Device (Relay) connected to GPIO 23:
  - Ensure the ESP32 is connected to your computer via USB for programming.
  
  Software Setup:
  - Arduino IDE with the ESP32 board package installed.
  - Blynk library installed.
  - Blynk IoT App installed on your smartphone.
  
 
*/

// Blynk Template Information 
#define BLYNK_TEMPLATE_ID "TMPL6OJCh4dyB"         //  Blynk Template ID
#define BLYNK_TEMPLATE_NAME "ESP32 Control"          //  Blynk Template Name
#define BLYNK_AUTH_TOKEN "Jphaomcm_HlqbiGQzAMiPjBISlwFYphO" //  Blynk Auth Token

// Enable debug printing to the Serial monitor
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi Credentials
// char ssid[] = "Demo";
// char pass[] = "12345678";


char ssid[] = "Vaibhav";
char pass[] = "Vaibhav@123";



// Define the GPIO pin used to control the device (Relay)
// In this case, we use GPIO 23 on the ESP32.
#define R1 23

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(115200);
  Serial.println("ESP32 Blynk Control - Starting up...");

  // Connect to the Blynk Cloud using the provided credentials and authentication token
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Configure the GPIO pin as an output
  pinMode(R1, OUTPUT);
  
  // Set the initial state of the device to OFF.
  // For an active-low device, setting the pin HIGH turns it off.
  digitalWrite(R1, HIGH);
  
  Serial.println("Setup complete. Waiting for commands from Blynk...");
}

// Blynk Virtual Pin Handling:
// When a command is sent from the Blynk app on Virtual Pin V1, this function is called.
BLYNK_WRITE(V1) { 
  // Read the value sent from the Blynk app (usually 0-Low or 225-High)
  int pinValue = param.asInt();
  
  // Print the received value to the Serial monitor for debugging
  Serial.print("Received command on V1: ");
  Serial.println(pinValue);
  
  // Write the value to the device connected to GPIO 23.
  // For an active-low device, LOW might turn it on and HIGH turn it off.
  digitalWrite(R1, pinValue);
}

void loop() {
  // Continuously run Blynk to process incoming commands
  Blynk.run();
}
