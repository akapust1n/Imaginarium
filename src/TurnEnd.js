import React, {Component} from 'react';
import getNames from "./users";
import './Game.css'
import './TurnEnd.css'
import vars from "./vars";

class TurnEnd extends Component {
    constructor(props) {
        super(props);
        this.state = {};
    }

    componentWillMount() {
        // let data = this.props.data;
        // let cards = data.cards;
        // let master = data.master;
        // this.setState(data);
        // getNames(cards.players, () => this.setState({cards: cards}));
        // getNames([master], result => this.setState({master: result[0]}));
        // this.setState({
        //     association: this.props.association,
        //     selected: cards.find(card => card.isCorrect)
        // });
    }

    render() {
        return (
            <div className='container'>
                <div className='row'>
                    <div className='col-4 Game-card-big center-content'>
                        <img height={'100%'} src='https://kapust1n.ru:5000/files/cards/049.jpg'/>
                    </div>
                    <div className='col-8'>
                        <div className='row'>
                            <div className='col-1'>
                                <button className='TurnEnd-btn-card'>
                                    <img className='Game-card' src='https://kapust1n.ru:5000/files/cards/049.jpg'/>
                                </button>
                            </div>
                            <div className='col-11'>
                                <div className='TurnEnd-player-name'>Колян Николаев (+4),</div>
                                <div className='TurnEnd-player-name'>Колян Николаев (+4),</div>
                                <div className='TurnEnd-player-name'>Колян Николаев (+4),</div>
                                <div className='TurnEnd-player-name'>Колян Николаев (+4),</div>
                                <div className='TurnEnd-player-name'>Колян Николаев (+4),</div>
                            </div>
                        </div>
                    </div>
                </div>
                <div className='row'>
                    <div className='col-10'>
                        Вася Васильев (+4):<br/>Какой ценой режиссер Ридли Скотт решил все проблемы, которые возникли вокруг его нового фильма «Все деньги мира».
                    </div>
                    <div className='col-2 center-content'>
                        <button className='btn btn-primary'>Продолжить</button>
                    </div>
                </div>
            </div>
        );
    }
}

export default TurnEnd;