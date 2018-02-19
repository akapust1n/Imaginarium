var WebSocket = require('ws')

var socket = new WebSocket("wss://kapust1n.ru:5000/ws");
socket.onopen = function() {
  console.log("Соединение установлено.");
   socket.send(JSON.stringify({
   type : "GameJoin"
}));
};




socket.onclose = function(event) {
  if (event.wasClean) {
    console.log('Соединение закрыто чисто');
  } else {
    console.log('Обрыв соединения'); // например, "убит" процесс сервера
  }
  console.log('Код: ' + event.code + ' причина: ' + event.reason);
};

socket.onmessage = function(event) {
  console.log("Получены данные " + event.data);
};

socket.onerror = function(error) {
 console.log("Ошибка " + error.message);
};
