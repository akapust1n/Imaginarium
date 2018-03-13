import React, {Component} from 'react';
import socket from "./socket";
import './Game.css'
import vars from './vars'
import getNames from "./users";
import renderRoot from "./director";
import CardSelect from './CardSelect'
import TurnEnd from "./TurnEnd";
import Alert from 'react-s-alert';
import 'react-s-alert/dist/s-alert-default.css';
import 'react-s-alert/dist/s-alert-css-effects/scale.css';
import Timer from 'react.timer'
import GameOver from "./GameOver";

class Game extends Component {
    constructor(props) {
        super(props);
        socket.setHandler('Association', content => this.initPlayerTurn(content));
        socket.setHandler('CardsOnBoard', content => this.renderGuessScreen(content));
        socket.setHandler('GameOver', content => renderRoot(<GameOver data={content}/>));
        socket.setHandler('AFK', content => {
                if (content.viewer_id === vars.viewer_id) {
                    let message = 'Вы не успели';
                    if (content.count === 4) {
                        message += '! Еще раз - кик!'
                    }
                    Alert.error(message, {
                        position: 'bottom-left',
                        effect: 'scale',
                        preserveContext: true
                    })
                } else {
                    getNames([content], () =>
                        Alert.info(content.name + ' не успел', {
                            position: 'bottom-left',
                            effect: 'scale',
                            preserveContext: true
                        })
                    )
                }
            }
        );
        socket.setHandler('DC', content =>
            getNames([content], () =>
                Alert.error(content.name + ' покинул игру', {
                    position: 'bottom-left',
                    effect: 'scale',
                    preserveContext: true
                })
            ));
        this.commit = this.commit.bind(this);
    }

    componentWillMount() {
        let data = this.props.data;
        data.isMasterTurn = true;
        data.association = '';
        data.commitEnabled = true;
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
                                <TurnTimer isMasterTurn={this.state.isMasterTurn}
                                           isMaster={vars.viewer_id === this.state.master}
                                           commitEnabled={this.state.commitEnabled}
                                />
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
                                <CommitButton association={this.state.association}
                                              onClick={this.commit}
                                              alert={Game.alert}
                                              hidden={
                                                  !((this.state.isMasterTurn && vars.viewer_id === this.state.master) ||
                                                      (!this.state.isMasterTurn && vars.viewer_id !== this.state.master))
                                              }
                                              disabled={!this.state.commitEnabled}/>
                            </div>
                        </div>
                    </div>
                </div>
                <Alert stack={{limit: 6}}/>
            </div>
        );
    }

    static alert(e) {
        e.preventDefault();
        Alert.error('Введите ассоциацию', {
            position: 'bottom-right',
            effect: 'scale',
            preserveContext: true
        });
    }

    initPlayerTurn(association) {
        this.setState({isMasterTurn: false, association: association, commitEnabled: true});
    }

    renderGuessScreen(cards) {
        renderRoot(<CardSelect association={this.state.association} cards={cards}/>)
    }

    selectCard(card) {
        this.setState({selected: card})
    }

    commit() {
        this.setState({commitEnabled: false});
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
            Alert.info('Ждем остальных', {
                position: 'bottom-right',
                effect: 'scale',
                preserveContext: true
            });
        }
    }

    setAssociation(association) {
        this.setState({association: association})
    }
}

class TurnTimer extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        let isMasterTurn = this.props.isMasterTurn;
        let isMaster = this.props.isMaster;
        let commitEnabled = this.props.commitEnabled;
        let startTime = isMaster ? 120 : 30;
        if (isMasterTurn && isMaster || (!isMasterTurn && !isMaster && commitEnabled)) {
            return (
                <div className='center-content'>
                    <img className='Game-timer-img' src='alarm-outline.png'/>
                    <div className='Game-timer'>
                        <Timer countDown startTime={startTime}/>
                    </div>
                </div>
            );
        }
        return (
            <div className='center-content'>
                <img className='Game-timer-img' src='alarm-outline.png'/>
            </div>
        );
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
        if (isMaster) {
            if (isMasterTurn) {
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
            return (
                <div className='Game-association'>
                    Ассоциация:<br/>{this.props.game.state.association}<br/><br/>Подождите, пока ходят игроки
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
        Alert.closeAll();
    }
}

class CommitButton extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        let association = this.props.association;
        let onClick = this.props.onClick;
        let alert = Game.alert;
        let hidden = this.props.hidden;
        let disabled = this.props.disabled;
        if (association) {
            return (
                <button className='btn btn-primary' onClick={onClick} hidden={hidden} disabled={disabled}>
                    Выбрать
                </button>
            );
        }
        return (
            <a className='btn btn-primary' href="#" onClick={alert} hidden={hidden}>Выбрать</a>
        );
    }
}

export default Game;