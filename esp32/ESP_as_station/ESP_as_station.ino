#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif

#include <WebSocketsServer.h>

#include <ArduinoJson.h>



#define LED1 21
#define LED2 22


char error_404[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Error 404 - Page Not Found</title>
<style>
  body {
    font-family: Arial, sans-serif;
    background-color: #f0f0f0;
    margin: 0;
    padding: 0;
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
  }
  .container {
    text-align: center;
  }
  h1 {
    font-size: 36px;
    color: #333;
  }
  p {
    font-size: 18px;
    color: #666;
  }
  a {
    color: #007bff;
    text-decoration: none;
  }
  a:hover {
    text-decoration: underline;
  }
</style>
</head>
<body>
  <div class="container">
    <h1>Error 404 - Page Not Found</h1>
    <p>The page you are looking for might have been removed, had its name changed, or is temporarily unavailable.</p>
    <p>Please <a href="/">return to the homepage</a> and try again.</p>
  </div>
</body>
</html>

)=====";

char loginPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Login</title>
<style>
  body {
    font-family: Arial, sans-serif;
    background-color: #f0f0f0;
    margin: 0;
    padding: 0;
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
  }
  form {
    background-color: #ffffff;
    padding: 20px;
    border-radius: 5px;
    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
    width: 300px;
  }
  h2 {
    margin-top: 0;
    text-align: center;
  }
  label {
    display: block;
    margin-bottom: 5px;
  }
  input[type="text"],
  input[type="password"] {
    width: 100%;
    padding: 8px;
    margin-bottom: 10px;
    border: 1px solid #ccc;
    border-radius: 4px;
    box-sizing: border-box;
  }
  input[type="submit"] {
    width: 100%;
    background-color: #4caf50;
    color: white;
    padding: 10px 20px;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    font-size: 16px;
  }
  input[type="submit"]:hover {
    background-color: #45a049;
  }
</style>
</head>
<body>
<form action="/login" method="post">
  <h2>Login</h2>
  <label for="username">Username:</label>
  <input type="text" id="username" name="username" required><br>
  <label for="password">Password:</label>
  <input type="password" id="password" name="password" required><br>
  <input type="submit" value="Login">
</form>
</body>
</html>

)=====";


char webpage[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>

<head>
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #f0f0f0;
      margin: 0;
      padding: 0;
    }

    center {
      display: block;
      margin-top: 50px;
    }

    h1 {
      color: #333;
      text-align: center;
    }

    h3 {
      color: #666;
    }

    button {
      background-color: #4CAF50;
      border: none;
      color: white;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
      border-radius: 5px;
    }

    button:hover {
      background-color: #45a049;
    }
  </style>

  <script>
    var connection = new WebSocket('ws://' + location.hostname + ':81/');

    var button_1_status = 0;
    var button_2_status = 0;

    function button_1_on() {
      button_1_status = 1;
      console.log("LED 1 is ON");
      send_data();
    }

    function button_1_off() {
      button_1_status = 0;
      console.log("LED 1 is OFF");
      send_data();
    }

    function button_2_on() {
      button_2_status = 1;
      console.log("LED 2 is ON");
      send_data();
    }

    function button_2_off() {
      button_2_status = 0;
      console.log("LED 2 is OFF");
      send_data();
    }

    function send_data() {
      var full_data = '{"LED1" :' + button_1_status + ',"LED2":' + button_2_status + '}';
      connection.send(full_data);
    }
  </script>
</head>

<body>

  <center>
    <h1>My Home Automation</h1>

    <h3> LED 1 </h3>
    <button onclick="button_1_on()">On</button>
    <button onclick="button_1_off()">Off</button>
    <br><br>
    <h3> LED 2 </h3>
    <button onclick="button_2_on()">On</button>
    <button onclick="button_2_off()">Off</button>

  </center>
</body>

</html>

)=====";

// ipaddress/led1/on
//ipaddress/led1/off

// ipaddress/led2/on
//ipaddress/led2/off
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80); // server port 80
WebSocketsServer websockets(81);

void notFound(AsyncWebServerRequest *request)
{
  //isAuthenticated=false;
  request->send_P(200, "text/html", error_404);
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) 
  {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        websockets.sendTXT(num, "Connected from server");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      String message = String((char*)( payload));
      Serial.println(message);

      
     DynamicJsonDocument doc(200);
    // deserialize the data
    DeserializationError error = deserializeJson(doc, message);
    // parse the parameters we expect to receive (TO-DO: error handling)
      // Test if parsing succeeds.
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  int LED1_status = doc["LED1"];
  int LED2_status = doc["LED2"];
  digitalWrite(LED1,LED1_status);
  digitalWrite(LED2,LED2_status);




  }
}




const char *ssid = "Vaibhav";
const char *password = "V@!b#@v98262151";
bool isAuthenticated = false; // Initialize authentication status



void setup(void)
{
  
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);

//esp as station point 
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
//-------------------------------


  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS responder started");
  }


  server.on("/", HTTP_GET, [&isAuthenticated](AsyncWebServerRequest *request) {
    // if (isAuthenticated) 
    // {
    //   request->send_P(200, "text/html", webpage);
    // } 
    // else 
    {
      isAuthenticated=false;
      request->send_P(200, "text/html", loginPage);
    }
  });

  server.on("/login", HTTP_POST, [&isAuthenticated](AsyncWebServerRequest *request) {
    String username = request->arg("username");
    String password = request->arg("password");

    // Perform login verification here
    if (username == "admin" && password == "123") {
      isAuthenticated = true;
      request->redirect("/webpage");
    } else {
      isAuthenticated = false;
      request->send(200, "text/plain", "Wrong username or password");
      //request->redirect("/");
    }
  });

  server.on("/webpage", HTTP_GET, [&isAuthenticated](AsyncWebServerRequest *request) {
    if (isAuthenticated) {
      request->send_P(200, "text/html", webpage);
    } else {
      request->redirect("/");
    }
  });




  server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED1,HIGH);
    request->send_P(200, "text/html", webpage);
  });

  server.onNotFound(notFound);

  server.begin();  // it will start webserver
  websockets.begin();
  websockets.onEvent(webSocketEvent);

}


void loop(void)
{
 websockets.loop();
}