import React, {Component} from 'react';
import logo from './logo.svg';
import './App.css';
import axios from 'axios'
import {w3cwebsocket as W3CWebSocket} from 'websocket'


class App extends Component {
    constructor() {
        super();
        this.vars = {};
        window.location.search.substring(1).split('&').forEach(pair => {
            let pairSplit = pair.split('=');
            this.vars[pairSplit[0]] = pairSplit[1];
        });
        this.state = {
            username: ''
        };
        this.socket = new W3CWebSocket("wss://kapust1n.ru:5000/ws");
        this.socket.onopen = function () {
            console.log("Соединение установлено.");
        };
        this.socket.onclose = function (event) {
            if (event.wasClean) {
                console.log('Соединение закрыто чисто');
            } else {
                console.log('Обрыв соединения');
            }
            console.log('Код: ' + event.code + ' причина: ' + event.reason);
        };
        this.socket.onmessage = function (event) {
            console.log("Получены данные " + event.data);
        };
        this.socket.onerror = function (error) {
            console.log("Ошибка " + error.message);
        };
        this.joinGame = this.joinGame.bind(this)
    }

    render() {
        return (
            <div className="App">
                <header className="App-header">
                    <img src={logo} className="App-logo" alt="logo"/>
                    <h1 className="App-title">Welcome to React</h1>
                </header>
                <p className="App-intro">
                    To get started, edit <code>src/App.js</code> and save to reload.
                </p>
                <button className='button' onClick={this.joinGame}>Играть</button>
                <p>{this.state.username}</p>
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
