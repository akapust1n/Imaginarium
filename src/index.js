import React from 'react';
import './index.css';
import App from './App';
import registerServiceWorker from './registerServiceWorker';
import renderRoot from './director'

renderRoot(<App/>);
registerServiceWorker();

