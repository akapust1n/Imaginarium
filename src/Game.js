import React, {Component} from 'react';
import socket from "./socket";
import './Game.css'
import vars from './vars'
import getNames from "./users";
import renderRoot from "./director";
import CardSelect from './CardSelect'
import TurnEnd from "./TurnEnd";

class Game extends Component {
    constructor(props) {
        super(props);
        socket.setHandler('Association', content => this.initPlayerTurn(content));
        socket.setHandler('CardsOnBoard', content => this.renderGuessScreen(content));
        this.commit = this.commit.bind(this);
    }

    componentWillMount() {
        let data = this.props.data;
        data.isMasterTurn = true;
        data.association = '';
        getNames(data.players, players => this.setState({players: players}));
        data.selected = data.hand[0];
        data.players.find((player) => player.viewer_id === vars.viewer_id).isViewer = true;
        this.setState(data);
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

                                </div>
                            </div>
                        </div>
                        <div className='row'>
                            <div className='col-12'>
                                <Association
                                    game={this}
                                    isMasterTurn={this.state.isMasterTurn}
                                    isMaster={vars.viewer_id === this.state.master}
                                />
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
                                <button className='btn btn-primary'
                                        onClick={this.commit}
                                        hidden={
                                            !((this.state.isMasterTurn && vars.viewer_id === this.state.master) ||
                                                (!this.state.isMasterTurn && vars.viewer_id !== this.state.master))
                                        }
                                >Выбрать
                                </button>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        );
    }

    initPlayerTurn(association) {
        this.setState({isMasterTurn: false, association: association});
    }

    renderGuessScreen(cards) {
        renderRoot(<CardSelect association={this.state.association} cards={cards}/>)
    }

    selectCard(card) {
        this.setState({selected: card})
    }

    commit() {
        socket.setHandler('TurnEnd', content => renderRoot(<TurnEnd data={content}
                                                                    association={this.state.association}/>));
        if (this.state.isMasterTurn) {
            let data = {
                'type': 'MasterTurn',
                'content': {
                    'card_id': this.state.selected.card_id,
                    'association': this.state.association
                }
            };
            console.log('sending', JSON.stringify(data));
            socket.send(JSON.stringify(data));
        } else {
            let data = {
                'type': 'PlayerTurn',
                'content': this.state.selected.card_id
            };
            console.log('sending', JSON.stringify(data));
            socket.send(JSON.stringify(data));
        }
    }

    setAssociation(association) {
        this.setState({association: association})
    }
}

class PlayerListItem extends Component {
    render() {
        let player = this.props.player;
        let master = this.props.master;
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
}

class PlayerList extends Component {
    render() {
        let listItems = this.props.players.map((player) =>
            <PlayerListItem key={player.viewer_id} player={player} master={this.props.master}/>);
        return (<ul className={'Game-players'}>{listItems}</ul>);
    }
}

class Association extends Component {
    constructor(props) {
        super(props);
        this.handleChange = this.handleChange.bind(this);
    }

    render() {
        let isMasterTurn = this.props.isMasterTurn;
        let isMaster = this.props.isMaster;
        if (isMasterTurn && isMaster) {
            return (
                <div className='form-group'>
                    <textarea className='Game-association-input form-control'
                              rows="3"
                              placeholder='Ассоциация'
                              onChange={this.handleChange}
                    />
                </div>
            );
        }
        if (isMasterTurn) {
            return (<p className='Game-association'>Ведущий придумывает ассоциацию</p>);
        }
        return (
            <div className='Game-association'>
                Ассоциация:<br/>{this.props.game.state.association}
            </div>
        );
    }

    handleChange(event) {
        this.props.game.setAssociation(event.target.value);
    }
}

export default Game;