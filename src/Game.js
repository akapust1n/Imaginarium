import React, {Component} from 'react';
import socket from "./socket";
import './Game.css'

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
            <div className="Game container">
                <div className='row'>
                    <div className='col-4 Game-left'>
                        <div className='row'>
                            <div className='col-12'>
                                <ul className={'Game-players'}>
                                    <li>1</li>
                                    <li>2</li>
                                    <li>3</li>
                                    <li>4</li>
                                    <li>5</li>
                                    <li>6</li>
                                </ul>
                            </div>
                        </div>
                        <div className='row'>
                            <div className='col-6'>
                                <div className='Game-deck'>
                                    60
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
                                <div className='Game-association'>
                                    Ассоциация:<br/>Содерберг окончательно вернулся в большое жанровое кино. Его снятый на айфон «Не в себе» способен пощекотать нервы покруче «Побочного эффекта» и «Заражения».
                                </div>
                            </div>
                        </div>
                    </div>
                    <div className='col-8 Game-right'>
                        <div className='row'>
                            <div className='col-12 Game-card-big center-content'>
                                <img height={'100%'} src={'https://kapust1n.ru:5000/files/cards/001.jpg'}/>
                            </div>
                        </div>
                        <div className='row'>
                            <div className='col-10'>
                                <div className='row'>
                                    <div className='col-2'>
                                        <button className='Game-btn-card'><img className='Game-card' src={'https://kapust1n.ru:5000/files/cards/001.jpg'}/></button>
                                    </div>
                                    <div className='col-2'>
                                        <button className='Game-btn-card'><img className='Game-card' src={'https://kapust1n.ru:5000/files/cards/001.jpg'}/></button>
                                    </div>
                                    <div className='col-2'>
                                        <button className='Game-btn-card'><img className='Game-card' src={'https://kapust1n.ru:5000/files/cards/001.jpg'}/></button>
                                    </div>
                                    <div className='col-2'>
                                        <button className='Game-btn-card'><img className='Game-card' src={'https://kapust1n.ru:5000/files/cards/001.jpg'}/></button>
                                    </div>
                                    <div className='col-2'>
                                        <button className='Game-btn-card'><img className='Game-card' src={'https://kapust1n.ru:5000/files/cards/001.jpg'}/></button>
                                    </div>
                                    <div className='col-2'>
                                        <button className='Game-btn-card'><img className='Game-card' src={'https://kapust1n.ru:5000/files/cards/001.jpg'}/></button>
                                    </div>
                                </div>
                            </div>
                            <div className='col-2 center-content'>
                                <button className='btn btn-primary'>Выбрать</button>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        );
    }

    updateState(data) {
        this.setState({players: data.players});
    }
}

export default Game;