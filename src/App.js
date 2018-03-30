import React, {Component} from 'react';
import './App.css';
import Rules from './Rules'
import Loading from './Loading'
import vars from './vars'
import socket from './socket'
import renderRoot from './director'

/**
 * Главное меню
 */
class App extends Component {
    constructor() {
        super();
        App.joinGame = App.joinGame.bind(this);
    }

    render() {
        return (
            <div className="App">
                <h1>Удачи и веселой игры!</h1>
                <div className='App-menu'>
                    <button className='btn btn-primary btn-lg btn-block App-menu-button'
                            onClick={App.joinGame}>Играть
                    </button>
                    <Rules/>
                </div>
            </div>
        );
    }

    /**
     * Начать игру
     */
    static joinGame() {
        renderRoot(<Loading/>);
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
