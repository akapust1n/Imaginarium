import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';

it('renders without crashing', () => {
    const div = document.createElement('div');
    let app = ReactDOM.render(<App/>, div);
    app.socket.close();
    ReactDOM.unmountComponentAtNode(div);
});
