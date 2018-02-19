import React, {Component} from 'react';
import './loader.css';
import './loading.css'

class Loading extends Component {
    constructor() {
        super();
        this.state = {
            status: ''
        };
        this.setStatus = this.setStatus.bind(this);
    }

    render() {
        return (
            <div className="Loading">
                <h2>{this.state.status}</h2>
                <div className='loader'>Loading...</div>
            </div>
        );
    }

    setStatus(status) {
        this.setState({status: status});
    }
}

export default Loading;