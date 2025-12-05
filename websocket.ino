#include "WiFi.h"
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// setting PWM properties
const int freq = 25000;
const int ledChannel = 0;
const int resolution = 8;
// the number of the LED pin
const int ledPin = 16;  // 16 corresponds to GPIO16

// the number of the LEDTWO pin
const int ledPinTwo = 17;

// the number of the LEDTHREE pin
const int ledPinThree = 18;

// the number of the LEDTHREE pin
const int ledPinFour = 19;


// setting PWM properties
const int ledChannelTwo = 1;

// setting PWM properties
const int ledChannelThree = 2;

// setting PWM properties
const int ledChannelFour = 3;







// Replace with your network credentials
const char* ssid = "myesp";
const char* password = "";



// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 600px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    padding-top:10px;
    padding-bottom:20px;
  }
  .button {
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .state {
     font-size: 1.5rem;
     color:#8c8c8c;
     font-weight: bold;
   }
  </style>
<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="topnav">
    <h1>ESP WebSocket Server</h1>
  </div>
  <div class="content">
    <div class="card">
      <h2>Output - GPIO 2</h2>
      <p class="state">state: <span id="state">%STATE%</span></p>
      <p><button id="button" class="button">Toggle</button></p>
    </div>
  </div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
    var state;
    if (event.data == "1"){
      state = "ON";
    }
    else{
      state = "OFF";
    }
    document.getElementById('state').innerHTML = state;
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  function initButton() {
    document.getElementById('button').addEventListener('click', toggle);
  }
  function toggle(){
    websocket.send(5 + "&" + "napredLeva");
    document.getElementById('state').innerHTML = 'WTF'
  }
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
        int leftTractNapredVal;

        int leftTractNazadVal;

        int rightTractNapredVal;

        int rightTractNazadVal;
//          digitalWrite(2, HIGH);
          Serial.println(val);
          Serial.println(valName);

        //left tract start
        if(valName == "napredLeva"){
          digitalWrite(2, HIGH);
          Serial.println("napredLeva ");
          leftTractNazadVal = 0;
          ledcWrite(ledChannelTwo, 0);
          
          leftTractNapredVal = val.toInt();
          ledcWrite(ledChannel, leftTractNapredVal);
        }

        if(valName == "nazadLeva"){
          leftTractNapredVal = 0;
          ledcWrite(ledChannel, 0);

          leftTractNazadVal = val.toInt();
          ledcWrite(ledChannelTwo, leftTractNazadVal);
          Serial.println("nazadLeva ");
          Serial.println(leftTractNazadVal);
        }
        //left track end

        //right track start
        if(valName == "napredDesna"){
          rightTractNazadVal = 0;
          ledcWrite(ledChannelFour, 0);
          
          rightTractNapredVal = val.toInt();
          ledcWrite(ledChannelThree, rightTractNapredVal);
        }

        if(valName == "nazadDesna"){
          rightTractNapredVal = 0;
          ledcWrite(ledChannelThree, 0);

          rightTractNazadVal = val.toInt();
          ledcWrite(ledChannelFour, rightTractNazadVal);
          Serial.println("nazadDesna ");
          Serial.println(rightTractNazadVal);
        }
//    moje brljotke


     
//     Serial.println("steps are " + val);
//     Serial.println("direction is " + valName);
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

//String processor(const String& var){
//  Serial.println(var);
//  if(var == "STATE"){
//    if (ledState){
//      return "ON";
//    }
//    else{
//      return "OFF";
//    }
//  }
//  return String();
//}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  pinMode(2, OUTPUT);
//  digitalWrite(2, HIGH);
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

  // Start server
  
  //MOTORS START
    // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  ledcSetup(ledChannelTwo, freq, resolution);
  ledcSetup(ledChannelThree, freq, resolution);
  ledcSetup(ledChannelFour, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
  
  //ledChannelTwo
  ledcAttachPin(ledPinTwo, ledChannelTwo);
  
  //ledChannelThree
  ledcAttachPin(ledPinThree, ledChannelThree);

  //ledChannelTwo
  ledcAttachPin(ledPinFour, ledChannelFour);

  
  //MOTORS END
  server.begin();
}


void loop() {
  ws.cleanupClients();
//  digitalWrite(ledPin, ledState);
}
