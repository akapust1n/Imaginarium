import React, {Component} from 'react';
import getNames from "./users";
import './Game.css'
import './TurnEnd.css'
import socket from "./socket";
import GameOver from "./GameOver";
import renderRoot from "./director";

class TurnEnd extends Component {
    constructor(props) {
        super(props);
        this.state = {};
        socket.setHandler('GameOver', content => renderRoot(<GameOver data={content}/>));
        TurnEnd.nextTurn = TurnEnd.nextTurn.bind(this);
    }

    componentWillMount() {
        let data = this.props.data;
        let cards = data.cards;
        let master = data.master;
        data.association = this.props.association;
        data.selected = cards.find(card => card.isCorrect);
        this.setState(data);
        cards.forEach(card => getNames(card.players, () => this.setState({cards: cards})));
        getNames([master], result => this.setState({master: result[0]}));
    }

    render() {
        return (
            <div className='container'>
                <div className='row'>
                    <div className='col-4 Game-card-big center-content'>
                        <img height={'100%'} src={this.state.selected.card_url}/>
                    </div>
                    <div className='col-8'>
                        {this.state.cards.map(card => <Card data={card} parent={this}/>)}
                    </div>
                </div>
                <div className='row'>
                    <div className='col-10'>
                        {this.state.master.name} (+{this.state.master.gain}):<br/>{this.state.association}
                    </div>
                    <div className='col-2 center-content'>
                        <button onClick={TurnEnd.nextTurn} className='btn btn-primary'>Продолжить</button>
                    </div>
                </div>
            </div>
        );
    }

    selectCard(card) {
        this.setState({selected: card})
    }

    static nextTurn() {
        let data = {'type': 'NextTurn'};
        console.log('sending', JSON.stringify(data));
        socket.send(JSON.stringify(data));
    }
}

class Card extends Component {
    render() {
        let card = this.props.data;
        let parent = this.props.parent;
        let className = 'row';
        if (card.isCorrect) {
            className += ' TurnEnd-correct'
        }
        return (
            <div className={className}>
                <div className='col-1'>
                    <button onClick={parent.selectCard.bind(parent, card)} className='TurnEnd-btn-card'>
                        <img className='Game-card' src={card.card_url}/>
                    </button>
                </div>
                <div className='col-11'>
                    {card.players.map((player, i, players) =>
                        <div className='TurnEnd-player-name'>
                            {player.name} (+{player.gain}){i === players.length - 1 ? '' : ','}
                        </div>
                    )}
                </div>
            </div>
        );
    }
}

export default TurnEnd;