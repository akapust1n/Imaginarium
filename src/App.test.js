import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';
import socket from './socket'
import vars from './vars'
import Game from "./Game";
import CardSelect from "./CardSelect";
import TurnEnd from "./TurnEnd";
import GameOver from "./GameOver";
import Loading from "./Loading";

beforeAll(() => {
    vars['access_token'] = process.env.vars_access_token;
    vars['viewer_id'] = process.env.vars_viewer_id;
});

it('render main menu', () => {
    const div = document.createElement('div');
    ReactDOM.render(<App/>, div);
    socket.close();
    ReactDOM.unmountComponentAtNode(div);
});

it('render loading', () => {
    const div = document.createElement('div');
    ReactDOM.render(<Loading/>, div);
    socket.close();
    ReactDOM.unmountComponentAtNode(div);
});

it('render game', () => {
    const div = document.createElement('div');
    ReactDOM.render(<Game data={JSON.parse('{"deck":48,"hand":[{"card_id":49,"card_url":"https://kapust1n.ru:5000/files/cards/049.jpg"},{"card_id":14,"card_url":"https://kapust1n.ru:5000/files/cards/014.jpg"},{"card_id":71,"card_url":"https://kapust1n.ru:5000/files/cards/071.jpg"},{"card_id":17,"card_url":"https://kapust1n.ru:5000/files/cards/017.jpg"},{"card_id":114,"card_url":"https://kapust1n.ru:5000/files/cards/114.jpg"},{"card_id":23,"card_url":"https://kapust1n.ru:5000/files/cards/023.jpg"}],"master":"40771774","players":[{"score":0,"viewer_id":"40771774"},{"score":0,"viewer_id":"21093986"}]}')}/>, div);
    socket.close();
    ReactDOM.unmountComponentAtNode(div);
});

it('render card select', () => {
    const div = document.createElement('div');
    ReactDOM.render(<CardSelect association={'Актер рассказал, с какой радостью он согласился переснять роль Кевина Спейси в фильме «Все деньги мира», и об особенностях работы с Ридли Скоттом.'} cards={JSON.parse('[{"card_id":49,"card_url":"https://kapust1n.ru:5000/files/cards/049.jpg"},{"card_id":14,"card_url":"https://kapust1n.ru:5000/files/cards/014.jpg"},{"card_id":71,"card_url":"https://kapust1n.ru:5000/files/cards/071.jpg"},{"card_id":17,"card_url":"https://kapust1n.ru:5000/files/cards/017.jpg"},{"card_id":114,"card_url":"https://kapust1n.ru:5000/files/cards/114.jpg"},{"card_id":23,"card_url":"https://kapust1n.ru:5000/files/cards/023.jpg"}]')}/>, div);
    socket.close();
    ReactDOM.unmountComponentAtNode(div);
});

it('render turn end', () => {
    const div = document.createElement('div');
    ReactDOM.render(<TurnEnd association='1231231' data={JSON.parse('{"master":{"viewer_id": 40771774, "gain": 3}, "cards":[{"card_id":49,"card_url":"https://kapust1n.ru:5000/files/cards/049.jpg","players":[{"viewer_id": 40771774, "gain": 3},{"viewer_id": 21093986, "gain": 2},{"viewer_id": 1, "gain": 4}]},{"card_id":14,"card_url":"https://kapust1n.ru:5000/files/cards/014.jpg","players":[{"viewer_id": 40771774, "gain": 3},{"viewer_id": 21093986, "gain": 2},{"viewer_id": 1, "gain": 4}]},{"card_id":71,"card_url":"https://kapust1n.ru:5000/files/cards/071.jpg","players":[{"viewer_id": 40771774, "gain": 3},{"viewer_id": 21093986, "gain": 2},{"viewer_id": 1, "gain": 4}]},{"card_id":17,"card_url":"https://kapust1n.ru:5000/files/cards/017.jpg","players":[]},{"card_id":18,"card_url":"https://kapust1n.ru:5000/files/cards/018.jpg","isCorrect": true, "players":[{"viewer_id": 40771774, "gain": 3},{"viewer_id": 21093986, "gain": 2},{"viewer_id": 1, "gain": 4}]}]}')}/>, div);
    socket.close();
    ReactDOM.unmountComponentAtNode(div);
});

it('render game over', () => {
    const div = document.createElement('div');
    ReactDOM.render(<GameOver data={JSON.parse('[{"score":12,"viewer_id":"21093986"},{"score":8,"viewer_id":"40771774"}]')}/>, div);
    socket.close();
    ReactDOM.unmountComponentAtNode(div);
});
