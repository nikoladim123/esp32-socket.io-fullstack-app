#include "WiFi.h"
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
//5 18 19 21

// assigning pin variable name
const int PINlevaNapred = 5;
const int PINlevaNazad = 18;
const int PINdesnaNapred = 21;
const int PINdesnaNazad = 19;





// Replace with your network credentials
const char* ssid = "MiniTank";
const char* password = "";



// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <style>
      html {
        height: 100%;
      }
      body {
        height: 100%;
        margin: 0;
        display: flex;
        align-items: center;
        justify-content: center;
      }

      .leftContainer {
        position: absolute;
        width: 30vw;
        height: 100%;
        left: 0;
        top: 0;
        display: flex;
        flex-direction: column;
        justify-content: space-between;
      }

      .rightContainer {
        position: absolute;
        width: 30vw;
        height: 100%;
        right: 0;
        top: 0;
        display: flex;
        flex-direction: column;
        justify-content: space-between;
      }

      div {
        box-sizing: border-box;
      }

      div > div {
        height: 30vw;
        width: 30vw;
        border: 1px solid black;
      }
      #fs {
        border: 1px solid black;
        width: 5vw;
        height: 5vw;
        display: flex;
        align-items: center;
        justify-content: center;
      }
    </style>
  </head>
  <body>
    <div id="fs">FS</div>
    <div class="leftContainer">
      <div id="LevaNapredGO"></div>
      <div id="LevaNazadGO"></div>
    </div>
    <div class="rightContainer">
      <div id="DesnaNapredGO"></div>
      <div id="DesnaNazadGO"></div>
    </div>

    <script>
      var gateway = `ws://192.168.4.1/`;
      var websocket;
      window.addEventListener("load", onload);


      function onload(event) {
        initWebSocket();
      }
      function onMessage() {
        console.log("fuck you");
      }

      function initWebSocket() {
        console.log("Trying to open a WebSocket connection…");
        websocket = new WebSocket(gateway);
        websocket.onopen = onOpen;
        websocket.onclose = onClose;
        websocket.onmessage = onMessage;
      }

      function onOpen(event) {
        console.log("Connection opened");
      }

      function onClose(event) {
        console.log("Connection closed");
        setTimeout(initWebSocket, 2000);
      }

      function sendRequest(value) {
        websocket.send(value);
      }
      const FS = document.getElementById("fs");
      fs.addEventListener("click", () => {
        document.documentElement.requestFullscreen();
      });

      const LevaNapredGO = document.getElementById("LevaNapredGO");
      const LevaNazadGO = document.getElementById("LevaNazadGO");
      const DesnaNapredGO = document.getElementById("DesnaNapredGO");
      const DesnaNazadGO = document.getElementById("DesnaNazadGO");

      LevaNapredGO.addEventListener("touchstart", (e) => {
        sendRequest("LevaNapredGO");
        LevaNapredGO.style.background = "red";
      });

      LevaNapredGO.addEventListener("touchend", (e) => {
        LevaNapredGO.style.background = "none";
        sendRequest("LevaNapredSTOP");
      });

      LevaNazadGO.addEventListener("touchstart", (e) => {
        sendRequest("LevaNazadGO");
        LevaNazadGO.style.background = "red";
      });

      LevaNazadGO.addEventListener("touchend", (e) => {
        sendRequest("LevaNazadSTOP");
        LevaNazadGO.style.background = "none";
      });

      DesnaNapredGO.addEventListener("touchstart", (e) => {
        sendRequest("DesnaNapredGO");
        DesnaNapredGO.style.background = "red";
      });

      DesnaNapredGO.addEventListener("touchend", (e) => {
        DesnaNapredGO.style.background = "none";
        sendRequest("DesnaNapredSTOP");
      });

      DesnaNazadGO.addEventListener("touchstart", (e) => {
        sendRequest("DesnaNazadGO");
        DesnaNazadGO.style.background = "red";
      });

      DesnaNazadGO.addEventListener("touchend", (e) => {
        DesnaNazadGO.style.background = "none";
        sendRequest("DesnaNazadSTOP");
      });
    </script>
  </body>

</html>
)rawliteral";

void notifyClients() {
//  ws.textAll(String(ledState));
}

String message = "";
String direction ="STOP";
String steps;
 String valName;
 String val;
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
//     Serial.printf((char*)data);
     message = (char*)data;
     val = message.substring(0, message.indexOf("&"));
     valName = message.substring(message.indexOf("&")+1, message.length());

//    moje brljotke      

        //LEAVA GUSENICA LOGIC
        if(message == "LevaNapredGO"){
            digitalWrite(PINlevaNapred,HIGH);
            digitalWrite(PINlevaNazad,LOW);
            Serial.printf("LevaNapredGO");
          }
        if(message == "LevaNazadGO"){
            digitalWrite(PINlevaNapred,LOW);
            digitalWrite(PINlevaNazad,HIGH);
            Serial.printf("LevaNazadGO");
          }
        if(message == "LevaNazadSTOP"){
            digitalWrite(PINlevaNazad,LOW);
            Serial.printf("LevaNazadSTOP");
          }
        if(message == "LevaNapredSTOP"){
            digitalWrite(PINlevaNapred,LOW);
            Serial.printf("LevaNapredSTOP");
          }

        //DESNA GUSENICA LOGIC
        if(message == "DesnaNapredGO"){
            digitalWrite(PINdesnaNapred,HIGH);
            digitalWrite(PINdesnaNazad,LOW);
            Serial.printf("DesnaNapredGO");
          }
        if(message == "DesnaNazadGO"){
            digitalWrite(PINdesnaNapred,LOW);
            digitalWrite(PINdesnaNazad,HIGH);
            Serial.printf("DesnaNazadGO");
          }
        if(message == "DesnaNapredSTOP"){
            digitalWrite(PINdesnaNapred,LOW);
            Serial.printf("DesnaNapredSTOP");
          }
        if(message == "DesnaNazadSTOP"){
            digitalWrite(PINdesnaNazad,LOW);
            Serial.printf("DesnaNazadSTOP");
          }

//    moje brljotke

     notifyClients();
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}



void setup(){
  WiFi.setHostname("tank.com");
  // Serial port for debugging purposes
  Serial.begin(115200);

//  digitalWrite(ledPin, LOW);
pinMode(PINlevaNapred, OUTPUT);
pinMode(PINlevaNazad, OUTPUT);
pinMode(PINdesnaNapred, OUTPUT);
pinMode(PINdesnaNazad, OUTPUT);


// Connect to Wi-2
//  WiFi.begin(ssid, password);
  WiFi.softAP(ssid);
  IPAddress IP = WiFi.softAPIP();

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });


  
  //MOTORS START
  //MOTORS END
  
  // Start server
  server.begin();
}


void loop() {
  ws.cleanupClients();
//  digitalWrite(ledPin, ledState);
}
