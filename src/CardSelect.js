import React, {Component} from "react";
import './Game.css'
import socket from "./socket";
import renderRoot from "./director";
import TurnEnd from "./TurnEnd";

class CardSelect extends Component {
    constructor(props) {
        super(props);
        this.state = {
            cards: [],
            selected: {}
        };
        this.commit = this.commit.bind(this);
    }

    componentWillMount() {
        socket.setHandler('TurnEnd', content => renderRoot(<TurnEnd data={content}
                                                                    association={this.props.association}/>));
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
                        <div className='row'>
                            <div className='col-12 Game-card-big center-content'>
                                <img height={'100%'} src={this.state.selected.card_url}/>
                            </div>
                        </div>
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
        let data = {
            'type': 'PlayerGuess',
            'content': this.state.selected.card_id
        };
        console.log('sending', JSON.stringify(data));
        socket.send(JSON.stringify(data));
    }
}

export default CardSelect;