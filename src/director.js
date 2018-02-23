import React from "react";
import ReactDOM from 'react-dom';

function renderRoot(component) {
    ReactDOM.unmountComponentAtNode(document.getElementById('root'));
    return ReactDOM.render(component, document.getElementById('root'));
}

export default renderRoot;