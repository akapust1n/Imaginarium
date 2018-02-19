import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';
import socket from './socket'

it('renders without crashing', () => {
    const div = document.createElement('div');
    ReactDOM.render(<App/>, div);
    socket.close();
    ReactDOM.unmountComponentAtNode(div);
});
