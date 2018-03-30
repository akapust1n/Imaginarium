import React from "react";
import ReactDOM from 'react-dom';

/**
 * Нарисовать компонент в элементе root
 * @param component Компонент
 * @returns Отрисованный компонент
 */
function renderRoot(component) {
    ReactDOM.unmountComponentAtNode(document.getElementById('root'));
    return ReactDOM.render(component, document.getElementById('root'));
}

export default renderRoot;