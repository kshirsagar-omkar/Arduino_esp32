#include "WiFi.h"



#define LED 23
#define LED1 22
#define PORT 80

WiFiServer server(PORT);

String ssid = "Vaibhav";
String password = "V@!b#@v98262151"; 

void setup()
{
  Serial.begin(115200);

  connect_to_wifi();
  pinMode(LED,OUTPUT);
  pinMode(LED1,OUTPUT);
  server.begin();

}

void loop()
{
  WiFiClient client = server.available();
  if(client)
  {
    handle_response(client);
  }
}

//====================================================================================================
void connect_to_wifi()
{
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(". ");
    delay(500);
  }

  Serial.println();
  
  Serial.print("NAME : ");
  Serial.println(WiFi.SSID());

  Serial.print("IP Adderess : ");
  Serial.println(WiFi.localIP());
}




//=======================================================================================================
void handle_response(WiFiClient &client) {
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  
  // Discard the rest of the request (up to the newline character)
  client.readStringUntil('\n');
  Serial.println("Request: " + req);

  // Process the request and control LEDs accordingly
  if (req.indexOf("/on0") != -1) {
    digitalWrite(LED, HIGH);
  } else if (req.indexOf("/off0") != -1) {
    digitalWrite(LED, LOW);
  } else if (req.indexOf("/on1") != -1) {
    digitalWrite(LED1, HIGH);
  } else if (req.indexOf("/off1") != -1) {
    digitalWrite(LED1, LOW);
  }

  // Send the HTTP response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  // Send the HTML content of the response
  client.println("<html><body>");
  client.println("<h1>ESP32 Web Server</h1>");
  client.println("<p>LED is now " + String(digitalRead(LED) == HIGH ? "ON" : "OFF") + "</p>");
  client.println("<a href='/on0'>Turn LED ON</a><br>");
  client.println("<a href='/off0'>Turn LED OFF</a>");

  client.println("<p>LED1 is now " + String(digitalRead(LED1) == HIGH ? "ON" : "OFF") + "</p>");
  client.println("<a href='/on1'>Turn LED1 ON</a><br>");
  client.println("<a href='/off1'>Turn LED1 OFF</a>");

  client.println("</body></html>");
}
