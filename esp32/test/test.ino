#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_SIZE 64

bool has_credentials() {
  return EEPROM.read(0) == 0x42 /* credentials marker */;
}

void save_credentials(char *ssid, char *pass) {
  char buf[EEPROM_SIZE];
  sprintf(buf, "%c%s:%s", 0x42, ssid, pass);
  EEPROM.writeString(0, buf);
  EEPROM.commit();
}

void load_credentials(char *ssid, char *pass) {
  if (!has_credentials()) {
    return;
  }
  char buf[EEPROM_SIZE];
  EEPROM.readString(1, buf, EEPROM_SIZE - 1);
  int i = 0;
  while ( i < EEPROM_SIZE && *(buf + i) != ':') {
    *ssid = *(buf + i);
    ssid++;
    i++;
  }
  *ssid = '\0';
  if (i == EEPROM_SIZE) {
    return;
  }
  i++;

  while ( i < EEPROM_SIZE && *(buf + i) != '\0') {
    *pass = *(buf + i);
    pass++;
    i++;
  }
  *pass = '\0';
}

void erase_credentials() {
  EEPROM.write(0, 0);
  EEPROM.commit();
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  if (!has_credentials()) {
    char *ssid = (char *) "alice";
    char *password = (char *) "s3cr3t";
    save_credentials(ssid, password);
    Serial.println("No credentials stored previously");
  } else {
    char ssid[32], password[32];
    load_credentials(ssid, password);
    Serial.println("Loaded credentials");
    Serial.printf("\tssid: %s\n", ssid);
    Serial.printf("\tpassword: %s\n", password);
    erase_credentials();
  }
}

void loop() {
  
}