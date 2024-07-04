#include <SPI.h>
#include <RF24.h>

#define CE_PIN 22
#define CSN_PIN 21

RF24 radio(CE_PIN, CSN_PIN);

// Define the address length
const int ADDRESS_LENGTH = 5;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.startListening();
}

void loop() {
  for (uint64_t address = 0x0000000000; address <= 0xFFFFFFFFFF; address++) {
    radio.openReadingPipe(1, address);
    radio.startListening();
    
    if (radio.available()) {
      char receivedData[32];
      radio.read(&receivedData, sizeof(receivedData));
      Serial.print("Received data on address 0x");
      Serial.print(address, HEX);
      Serial.print(": ");
      Serial.println(receivedData);
    }
    
    radio.stopListening();
  }
}
