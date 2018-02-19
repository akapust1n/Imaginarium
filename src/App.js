import React, {Component} from 'react';
import './App.css';
import './loader.css';
import axios from 'axios'
import Socket from './socket'
import Rules from './Rules'


class App extends Component {
    constructor() {
        super();
        this.vars = {};
        window.location.search.substring(1).split('&').forEach(pair => {
            let pairSplit = pair.split('=');
            this.vars[pairSplit[0]] = pairSplit[1];
        });
        this.socket = Socket.getInstance();
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
