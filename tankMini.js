// ajax
// function sendRequest(name, value) {
//     var xhttp = new XMLHttpRequest();
//     xhttp.onreadystatechange = function() {
//         if (this.readyState == 4 && this.status == 200) {
//             return;
//         }
//     };
//     xhttp.open("GET", "http://192.168.4.1/?" + name + "=" + value, true);
//     xhttp.setRequestHeader('Connection', 'keep-alive');
//     xhttp.send();
// }

//ajax end

//   reverse/forward buttons
//   reverse/forward buttons
//   reverse/forward buttons

// WEB SOCKET
var gateway = `ws://192.168.4.1/`;
var websocket;
window.addEventListener("load", onload);
// var direction;

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
// console.log("WTSSS");
// WEB SOCKET


// function getHeightVW(y) {
//   return y / (window.innerHeight / 100);
// }



const FS = document.getElementById("fs");
fs.addEventListener("click", () => {
  document.documentElement.requestFullscreen();
});

const LevaNapredGO = document.getElementById("LevaNapredGO");
const LevaNazadGO = document.getElementById("LevaNazadGO");
const DesnaNapredGO = document.getElementById("DesnaNapredGO");
const DesnaNazadGO = document.getElementById("DesnaNazadGO");

//leva napred
LevaNapredGO.addEventListener("touchstart", (e) => {
  sendRequest("LevaNapredGO");
  LevaNapredGO.style.background = "red";
});

LevaNapredGO.addEventListener("touchend", (e) => {
  LevaNapredGO.style.background = "none";
  sendRequest("LevaNapredSTOP");
});

// leva nazad
LevaNazadGO.addEventListener("touchstart", (e) => {
  sendRequest("LevaNazadGO");
  LevaNazadGO.style.background = "red";
});

LevaNazadGO.addEventListener("touchend", (e) => {
  sendRequest("LevaNazadSTOP");
  LevaNazadGO.style.background = "none";
});

//desna napred
DesnaNapredGO.addEventListener("touchstart", (e) => {
  sendRequest("DesnaNapredGO");
  DesnaNapredGO.style.background = "red";
  //   }
});

DesnaNapredGO.addEventListener("touchend", (e) => {
  DesnaNapredGO.style.background = "none";
  sendRequest("DesnaNapredSTOP");
});

//desna nazad
DesnaNazadGO.addEventListener("touchstart", (e) => {
  sendRequest("DesnaNazadGO");
  DesnaNazadGO.style.background = "red";
});

DesnaNazadGO.addEventListener("touchend", (e) => {
  DesnaNazadGO.style.background = "none";
  sendRequest("DesnaNazadSTOP");
});

