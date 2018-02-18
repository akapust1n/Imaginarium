import React, {Component} from 'react';
import logo from './logo.svg';
import './App.css';
import axios from 'axios'


class App extends Component {
    constructor () {
        super();
        this.state = {
            username: ''
        };
        App.handleClick = App.handleClick.bind(this)
    }

    render() {
        return (
            <div className="App">
                <header className="App-header">
                    <img src={logo} className="App-logo" alt="logo"/>
                    <h1 className="App-title">Welcome to React</h1>
                </header>
                <p className="App-intro">
                    To get started, edit <code>src/App.js</code> and save to reload.
                </p>
                <button className='button' onClick={App.handleClick}>Click Me</button>
                <p>{this.state.username}</p>
            </div>
        );
    }

    static handleClick () {
        axios.get('https://kapust1n.ru:5000/').then(
            response => this.setState({username: response.data}),
            error => console.log(error)
        );
    }
}

export default App;
