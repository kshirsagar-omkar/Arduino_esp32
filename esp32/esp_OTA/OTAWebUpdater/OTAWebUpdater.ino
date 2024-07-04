#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>


#include <WebSocketsServer.h>

#include <ArduinoJson.h>

// ipaddress/led1/on
//ipaddress/led1/off

// ipaddress/led2/on
//ipaddress/led2/off
#include <ESPAsyncWebServer.h>


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

    .container {
      background-color: #ffffff;
      padding: 20px;
      border-radius: 10px;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
      width: 300px;
      text-align: center;
    }

    h2 {
      margin-top: 0;
      font-size: 24px;
    }

    label {
      display: block;
      margin-bottom: 10px;
      font-size: 16px;
    }

    input[type="text"],
    input[type="password"] {
      width: 100%;
      padding: 8px;
      margin-bottom: 20px;
      border: 1px solid #ccc;
      border-radius: 4px;
      box-sizing: border-box;
      font-size: 16px;
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
  <div class="container">
    <h2>Login</h2>
    <form action="/login" method="post">
      <label for="username">Username:</label>
      <input type="text" id="username" name="username" required><br>
      <label for="password">Password:</label>
      <input type="password" id="password" name="password" required><br>
      <input type="submit" value="Login">
    </form>
  </div>
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
      text-align: center;
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

    input[type="text"] {
      padding: 10px;
      margin-bottom: 15px;
      border: 2px solid #4CAF50;
      border-radius: 5px;
      box-sizing: border-box;
      font-size: 16px;
      width: 15%;
    }

    .mac-address {
      font-size: 18px;
      font-weight: bold;
      color: #333;
      margin-bottom: 10px;
    }
  </style>

  <script>
    var connection = new WebSocket('ws://' + location.hostname + ':81/');

    var button_1_status = 0;
    var button_2_status = 0;
    var macAddress = '';

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
      if (macAddress === '') {
        alert('Please enter a MAC address!');
        return;
      }
      var full_data = '{"LED1" :' + button_1_status + ',"LED2":' + button_2_status + ',"MAC":"' + macAddress + '"}';
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
    <br><br>
    <h3 class="mac-address">Enter MAC Address</h3>
    <input type="text" id="macAddress" placeholder="MAC Address" onchange="macAddress = this.value" required>
    <br><br>
  </center>
</body>

</html>


)=====";




/*===========================*/
const char* host = "esp32";
const char* ssid = "Vaibhav";
const char* password = "V@!b#@v98262151";

//WebServer server(80);

/*
 * Login page
 */

char loginIndex[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 Login Page</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #f0f0f0;
      margin: 0;
      padding: 0;
    }

    .container {
      max-width: 400px;
      margin: 50px auto;
      padding: 20px;
      background-color: #fff;
      border-radius: 8px;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
    }

    h1 {
      margin-top: 0;
      text-align: center;
    }

    form {
      margin-top: 20px;
    }

    input[type="text"],
    input[type="password"] {
      width: 100%;
      padding: 10px;
      margin-bottom: 10px;
      border: 1px solid #ccc;
      border-radius: 5px;
      box-sizing: border-box;
    }

    input[type="submit"] {
      width: 100%;
      padding: 10px;
      background-color: #4CAF50;
      border: none;
      border-radius: 5px;
      color: white;
      cursor: pointer;
    }

    input[type="submit"]:hover {
      background-color: #45a049;
    }

    .error-message {
      color: red;
      font-size: 14px;
      margin-top: 10px;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>ESP32 Login Page</h1>
    <form name="loginForm" method="post" action="/upload_code_login">
      <input type="text" name="userid" placeholder="Username">
      <input type="password" name="pwd" placeholder="Password">
      <input type="submit" value="Login">
    </form>
  </div>
</body>
</html>



)=====";
 

/*
 * Server Index Page
 */

char serverIndex[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>File Upload</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      margin: 20px;
    }
    .container {
      max-width: 600px;
      margin: 40px auto;
      padding: 20px;
      background-color: #f9f9f9;
      border: 1px solid #ddd;
      border-radius: 10px;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
    }
    h1 {
      margin-top: 0;
    }
    form {
      margin-bottom: 20px;
    }
    input[type="file"] {
      padding: 10px;
      border: 1px solid #ccc;
      border-radius: 5px;
    }
    input[type="submit"] {
      background-color: #4CAF50;
      color: #fff;
      padding: 10px 20px;
      border: none;
      border-radius: 5px;
      cursor: pointer;
    }
    input[type="submit"]:hover {
      background-color: #3e8e41;
    }
    #prg-container {
      width: 100%;
      background-color: #f3f3f3;
      border: 1px solid #ddd;
      border-radius: 5px;
      margin-bottom: 20px;
      height: 30px;
      position: relative;
    }
    #prg-bar {
      height: 100%;
      background-color: #4CAF50;
      width: 0%;
      border-radius: 5px;
      position: absolute;
      top: 0;
      left: 0;
      text-align: center;
      line-height: 30px;
      color: white;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>File Uploader</h1>
    <form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>
      <input type='file' name='update'>
      <input type='submit' value='Update'>
    </form>
    <div id='prg-container'>
      <div id="prg-bar">0%</div>
    </div>
  </div>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
  <script>
    $('form').submit(function(e){
      e.preventDefault();
      var form = $('#upload_form')[0];
      var data = new FormData(form);
      $.ajax({
        url: '/update',
        type: 'POST',
        data: data,
        contentType: false,
        processData:false,
        xhr: function() {
          var xhr = new window.XMLHttpRequest();
          xhr.upload.addEventListener('progress', function(evt) {
            if (evt.lengthComputable) {
              var per = evt.loaded / evt.total;
              $('#prg-bar').css('width', Math.round(per*100) + '%').text(Math.round(per*100) + '%');
            }
          }, false);
          return xhr;
        },
        success:function(d, s) {
          console.log('Success!');
        },
        error: function (a, b, c) {
          console.error('Error!');
        }
      });
    });
  </script>
</body>
</html>
)=====";
/*===========================*/





AsyncWebServer server(80); // server port 80
WebSocketsServer websockets(81);


void notFound(AsyncWebServerRequest *request)
{
  //isAuthenticated=false;
  request->send_P(404, "text/html", error_404);
}



String macAddress = WiFi.macAddress();
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


    if(doc["MAC"] == macAddress || doc["MAC"] == "omkar1")  //String macAddress = WiFi.macAddress();
    {
      int LED1_status = doc["LED1"];
      int LED2_status = doc["LED2"];
      digitalWrite(LED1,LED1_status);
      digitalWrite(LED2,LED2_status);
    }

  }
}



bool isAuthenticated = false; // Initialize authentication status
bool isUploadAuthenticated = false; // Flag to track authentication status
/*
 * setup function
 */
void setup(void) {
  Serial.begin(115200);

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());


  /*=========================*/
  
  /*return index page which is stored in serverIndex */

  // Handler for upload_code login page


  server.on("/upload_code", HTTP_GET, [&isUploadAuthenticated](AsyncWebServerRequest *request) {
    {
      request->send_P(200, "text/html", loginIndex);
    }
  });

  server.on("/upload_code_login", HTTP_POST, [&isUploadAuthenticated](AsyncWebServerRequest *request){
    // Get the username and password from the request
    String userid = request->arg("userid");
    String pwd = request->arg("pwd");

    // Check if the credentials match
    if (userid.equals("admin") && pwd.equals("123")) {
        isUploadAuthenticated = true; // Set authentication flag
        request->redirect("/serverIndex"); // Redirect to server index page
    } else {
      isUploadAuthenticated = false; // Set authentication flag
        request->redirect("/upload_code");
    }
  });

  // Handler for server index page
  server.on("/serverIndex", HTTP_GET, [&isUploadAuthenticated](AsyncWebServerRequest *request) {
    if (isUploadAuthenticated) {
        request->send_P(200, "text/html", serverIndex); // Serve the server index page
    } else {
        isUploadAuthenticated = false; // Set authentication flag
        request->redirect("/upload_code"); 
    }
  });


  server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    if (!Update.hasError()) {
      ESP.restart();
    }
  }, [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    if (!index) {
      Serial.printf("Update: %s\n", filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
        Update.printError(Serial);
      }
    }
    if (len) {
      if (Update.write(data, len) != len) {
        Update.printError(Serial);
      }
    }
    if (final) {
      if (Update.end(true)) {
        Serial.printf("Update Success: %u\nRebooting...\n", index + len);
      } else {
        Update.printError(Serial);
      }
    }
  });
/*=========================*/





  server.on("/", HTTP_GET, [&isAuthenticated](AsyncWebServerRequest *request) {
    // if (isAuthenticated) 
    // {
    //   request->send_P(200, "text/html", webpage);
    // } 
    // else 
    {
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


  server.begin();
  websockets.begin();
  websockets.onEvent(webSocketEvent);

}

void loop(void) {
  //server.handle();
  // delay(1);
  websockets.loop();
  // digitalWrite(LED1,HIGH);
  // delay(100);
  // digitalWrite(LED1,LOW);
  // delay(100);
}
