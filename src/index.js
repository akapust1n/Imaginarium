import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './App';
import registerServiceWorker from './registerServiceWorker';
import {w3cwebsocket as W3CWebSocket} from "websocket";

ReactDOM.render(<App/>, document.getElementById('root'));
registerServiceWorker();

window.vars = {};
window.location.search.substring(1).split('&').forEach(pair => {
    let pairSplit = pair.split('=');
    window.vars[pairSplit[0]] = pairSplit[1];
});

window.socket = new W3CWebSocket("wss://kapust1n.ru:5000/ws");
window.socket.onopen = () => console.log("Соединение установлено.");
window.socket.onclose = event => {
    if (event.wasClean) {
        console.log('Соединение закрыто чисто');
    } else {
        console.log('Обрыв соединения');
    }
    console.log('Код: ' + event.code + ' причина: ' + event.reason);
};
window.socket.onerror = error => console.log("Ошибка " + error.message);
window.socket.handlers = {};
window.socket.addHandler = function (type, handler) {
    window.socket.handlers[type] = handler;
};
window.socket.onmessage = event => {
    console.log("Получены данные " + event.data);
    let data = JSON.parse(event.data);
    let type = data.type;
    if (!type) {
        return;
    }
    let handler = window.socket.handlers[type];
    if (handler) {
        handler(data.content);
    }
};
