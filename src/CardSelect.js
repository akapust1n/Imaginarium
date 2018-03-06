import React, {Component} from "react";
import './Game.css'
import socket from "./socket";
import Timer from 'react.timer'

class CardSelect extends Component {
    constructor(props) {
        super(props);
        this.state = {
            cards: [],
            selected: {},
            commitEnabled: true
        };
        this.commit = this.commit.bind(this);
    }

    componentWillMount() {
        let cards = this.props.cards.filter(card => !card.isOwn);
        this.setState({cards: cards, selected: cards[0]});
    }

    render() {
        return (
            <div className='container'>
                <div className='row'>
                    <div className='col-3 Game-association'>
                        Ассоциация:<br/>{this.props.association}
                    </div>
                    <div className='col-9 Game-card-big'>
                        <div className='Game-card-big center-content'>
                            <img height={'100%'} src={this.state.selected.card_url}/>
                        </div>
                    </div>
                </div>
                <div className='row'>
                    <div className='col-3 center-content'>
                        <img className='Game-timer-img' src='alarm-outline.png'/>
                        <div className='Game-timer'>
                            <Timer countDown startTime={30}/>
                        </div>
                    </div>
                    <div className='col=9'>
                        <div className='row'>
                            <div className='col-10'>
                                <div className='row'>
                                    {this.state.cards.map(card =>
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
                                        disabled={!this.state.commitEnabled}
                                >Выбрать
                                </button>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        );
    }

    selectCard(card) {
        this.setState({selected: card})
    }

    commit() {
        this.setState({commitEnabled: false});
        let data = {
            'type': 'PlayerGuess',
            'content': this.state.selected.card_id
        };
        console.log('sending', JSON.stringify(data));
        socket.send(JSON.stringify(data));
    }
}

export default CardSelect;