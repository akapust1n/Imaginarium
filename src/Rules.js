import React, {Component} from "react";
import rules from './rules-content';

class Rules extends Component {
    constructor() {
        super();
        this.state = {
            displayRules: false
        };
        this.showRules = this.showRules.bind(this);
    }

    render() {
        return (
            <div className="Rules">
                <button className='btn btn-light btn-lg btn-block App-menu-button' onClick={this.showRules}
                        hidden={this.state.displayRules}>Правила
                </button>
                <div className='App-rules' hidden={!this.state.displayRules}>{rules}</div>
            </div>
        );
    }

    showRules() {
        this.setState({displayRules: true});
    }
}

export default Rules;