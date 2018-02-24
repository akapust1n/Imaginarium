import React, {Component} from 'react';
import socket from "./socket";
import './Game.css'
import vars from './vars'
import getNames from "./users";

class Game extends Component {
    constructor() {
        super();
        this.state = {
            stage: 'MasterTurn',
            association: ''
        };
        socket.setHandler('MasterTurn', content => this.initState(content));
        this.initState = this.initState.bind(this);
        this.commit = this.commit.bind(this);
    }

    render() {
        return (
            <div className="Game container">
                <div className='row'>
                    <div className='col-4 Game-left'>
                        <div className='row'>
                            <div className='col-12'>
                                <PlayerList players={this.state.players} master={this.state.master}/>
                            </div>
                        </div>
                        <div className='row'>
                            <div className='col-6'>
                                <div className='Game-deck'>
                                    {this.state.deck}
                                </div>
                            </div>
                            <div className='col-6'>
                                <div className='Game-timer'>
                                    тут будет таймер
                                </div>
                            </div>
                        </div>
                        <div className='row'>
                            <div className='col-12'>
                                <Association isMaster={vars.viewer_id === this.state.master}
                                             association={this.state.association}/>
                            </div>
                        </div>
                    </div>
                    <div className='col-8 Game-right'>
                        <div className='row'>
                            <div className='col-12 Game-card-big center-content'>
                                <img height={'100%'} src={this.state.selected.card_url}/>
                            </div>
                        </div>
                        <div className='row'>
                            <div className='col-10'>
                                <div className='row'>
                                    {this.state.hand.map(card =>
                                        <div className='col-2'>
                                            <button onClick={this.selectCard.bind(this, card)}
                                                    className='Game-btn-card'>
                                                <img className='Game-card' src={card.card_url}/>
                                            </button>
                                        </div>)}
                                </div>
                            </div>
                            <div className='col-2 center-content'>
                                <button className='btn btn-primary' onClick={this.commit}>Выбрать</button>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        );
    }

    initState(data) {
        getNames(data.players);
        data.selected = data.hand[0];
        data.players.find((player) => player.viewer_id === vars.viewer_id).isViewer = true;
        this.setState(data);
    }

    selectCard(card) {
        this.setState({selected: card})
    }

    commit() {
        switch (this.state.stage) {
            case 'MasterTurn':
                let data = {
                    'type': 'MasterTurn',
                    'content': {
                        'card_id': this.state.selected.card_id,
                        'association': this.state.association
                    }
                };
                console.log(JSON.stringify(data));
                socket.send(JSON.stringify(data));
        }
    }
}

function PlayerListItem(props) {
    let player = props.player;
    let master = props.master;
    if (player.isViewer && player.viewer_id === master) {
        return (<li><b><u>{player.name}</u></b> - {player.score}</li>);
    }
    if (player.isViewer) {
        return (<li><b>{player.name}</b> - {player.score}</li>);
    }
    if (player.viewer_id === master) {
        return (<li><u>{player.name}</u> - {player.score}</li>);
    }
    return (<li>{player.name} - {player.score}</li>);
}

function PlayerList(props) {
    let listItems = props.players.map((player) =>
        <PlayerListItem key={player.viewer_id} player={player} master={props.master}/>);
    return (<ul className={'Game-players'}>{listItems}</ul>);
}

function Association(props) {
    let isMaster = props.isMaster;
    let association = props.association;
    if (association) {
        return (
            <div className='Game-association'>
                Ассоциация:<br/>{association}
            </div>
        );
    }
    if (isMaster) {
        return (
            <div className='form-group'>
                <textarea className='Game-association-input form-control' rows="3" placeholder='Ассоциация'></textarea>
            </div>
        );
    }
    return (<p className='Game-association'>Ведущий придумывает ассоциацию</p>);
}

export default Game;