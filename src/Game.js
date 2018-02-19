import React, {Component} from 'react';
import socket from "./socket";

class Game extends Component {
    constructor() {
        super();
        this.state = {
            players: []
        };
        socket.setHandler('MasterTurn', content => this.updateState(content));
        this.updateState = this.updateState.bind(this);
    }

    render() {
        return (
            <div className="Game">
                {this.state.players}
            </div>
        );
    }

    updateState(data) {
        this.setState({players: data.players});
    }
}

export default Game;