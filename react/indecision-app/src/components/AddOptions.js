import React from 'react';

class AddOptions extends React.Component {

    constructor(props) {
        super(props);
        this.handleSubmit = this.handleSubmit.bind(this);
        this.state = {
            error: undefined
        };
    }

    handleSubmit(e) {
        e.preventDefault();

        const value = e.target.elements.texto.value.trim();
        const error = this.props.addOption(value);
        if (!error) {
            e.target.elements.texto.value = '';
        }

        this.setState(() => ({error}));

    }

    render() {
        return (
            <div>
                {this.state.error && <p>{this.state.error}</p>}
                <form onSubmit={this.handleSubmit}>
                    <input name='texto' type="text" placeholder="type a new option here" />
                    <button>Add it</button>
                </form>
            </div>
        );
    }
};

export default AddOptions;
