import React, {Component} from "react";
import getNames from "./users";
import './App.css'
import './GameOver.css'
import renderRoot from "./director";
import App from "./App";

class GameOver extends Component {
    constructor(props) {
        super(props);
        this.state = {players: []};
        GameOver.menu = GameOver.menu.bind(this);
    }

    componentWillMount() {
        let players = this.props.data;
        players.sort((a, b) => b.score - a.score);
        getNames(players, () => this.setState({players: players}));
    }

    render() {
        return (
            <div className="container">
                <div className='row'>
                    <div className='col-4 offset-4'>
                        <h2>Игра окончена</h2>
                        <ol>
                            {this.state.players.map(player => (<li>{player.name} - {player.score}</li>))}
                        </ol>
                        <div className='row justify-content-end'>
                            <button className='btn btn-primary' onClick={GameOver.menu}>
                                Меню
                            </button>
                        </div>
                    </div>
                </div>
            </div>
        );
    }

    static menu() {
        renderRoot(<App/>);
    }
}

export default GameOver;