import React, {Component} from 'react';
import ReactDOM from 'react-dom';
import axios from 'axios'
import './App.css';
import Rules from './Rules'
import Loading from './Loading'
import vars from './vars'
import socket from './socket'

class App extends Component {
    constructor() {
        super();
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
        ReactDOM.unmountComponentAtNode(document.getElementById('root'));
        let loading = ReactDOM.render(<Loading/>, document.getElementById('root'));
        loading.setStatus('Авторизация...');
        socket.addHandler('Error', content => loading.setStatus(content));
        socket.addHandler('Queue', () => loading.setStatus('Подбор игроков...'));
        let data = {
            'type': 'GameJoin',
            'content': {
                'viewer_id': vars['viewer_id'],
                'api_id': vars['api_id'],
                'auth_key': vars['auth_key']
            }
        };
        console.log(JSON.stringify(data));
        socket.send(JSON.stringify(data));
    }
}

export default App;
