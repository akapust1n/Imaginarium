import React, {Component} from 'react';
import './loader.css';
import './loading.css'
import socket from "./socket";
import renderRoot from "./director";
import Game from "./Game";

class Loading extends Component {
    constructor() {
        super();
        this.state = {
            status: 'Авторизация...'
        };
        this.setStatus = this.setStatus.bind(this);
        socket.setHandler('Error', content => this.setStatus(content));
        socket.setHandler('Queue', () => this.setStatus('Подбор игроков...'));
        socket.setHandler('MasterTurn', content => {
            let game = renderRoot(<Game/>);
            game.initState(content);
        });
    }

    render() {
        return (
            <div className="Loading">
                <h2>{this.state.status}</h2>
                <div className='loader'>Loading...</div>
            </div>
        );
    }

    setStatus(status) {
        this.setState({status: status});
    }
}

export default Loading;