import React, {Component} from 'react';
import './App.css';
import axios from 'axios'
import {w3cwebsocket as W3CWebSocket} from 'websocket'
import Rules from './Rules'


class App extends Component {
    constructor() {
        super();
        this.vars = {};
        window.location.search.substring(1).split('&').forEach(pair => {
            let pairSplit = pair.split('=');
            this.vars[pairSplit[0]] = pairSplit[1];
        });
        this.socket = new W3CWebSocket("wss://kapust1n.ru:5000/ws");
        this.socket.onopen = () => console.log("Соединение установлено.");
        this.socket.onclose = event => {
            if (event.wasClean) {
                console.log('Соединение закрыто чисто');
            } else {
                console.log('Обрыв соединения');
            }
            console.log('Код: ' + event.code + ' причина: ' + event.reason);
        };
        this.socket.onmessage = event => console.log("Получены данные " + event.data);
        this.socket.onerror = error => console.log("Ошибка " + error.message);
        this.joinGame = this.joinGame.bind(this);
    }

    render() {
        return (
            <div className="App">
                <h1>Удачи и веселой игры!</h1>
                <div className='App-menu'>
                    <button className='btn btn-primary btn-lg btn-block App-menu-button'
                            onClick={this.joinGame}>Играть
                    </button>
                    <Rules/>
                </div>
            </div>
        );
    }

    joinGame() {
        let data = {
            'type': 'GameJoin',
            'content': {
                'viewer_id': this.vars['viewer_id'],
                'api_id': this.vars['api_id'],
                'auth_key': this.vars['auth_key']
            }
        };
        this.socket.send(JSON.stringify(data));
    }
}

export default App;
