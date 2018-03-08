class IndecisionApp extends React.Component {
    constructor(props) {
        super(props);
        this.handleDeleteOptions = this.handleDeleteOptions.bind(this);
        this.handlePick = this.handlePick.bind(this);
        this.state = {
            options: ['one', 'two', 'five', 'six']
        };
    }

    handlePick() {
        const idx = Math.floor(Math.random() * this.state.options.length);
        alert(this.state.options[idx]);
    }

    handleDeleteOptions() {
        this.setState(() => {
            return {
                options: []
            };
        });
    }

    render() {
        const title = 'Indecision';
        const subtitle = 'Put your life in the hands of a computer!';

        return (
            <div>
                <Header title={title} subtitle={subtitle}/>
                <Action
                    hasOptions={this.state.options.length > 0}
                    pick={this.handlePick}
                />
                <Options
                    options={this.state.options}
                    hasOptions={this.state.options.length > 0}
                    deleteOptions={this.handleDeleteOptions}
                />
                <AddOptions />
            </div>
        );
    };
};

class Header extends React.Component {
    /* you must define render */
    render() {
        console.log(this.props);
        return (
            <div>
                <h1>{this.props.title}</h1>
                <h2>{this.props.subtitle}</h2>
            </div>
        );
    }
};

class Action extends React.Component {
    render() {
        return (
            <div>
                <button
                    disabled={!this.props.hasOptions}
                    onClick={this.props.pick}>What Should I do?</button>
            </div>
        );
    }
};

class Options extends React.Component {
    //constructor(props) {
        //super(props);
        /* We do this to have a better performance.
         * This way we don't have to call bind for each time the componet
         * gets a render call
         */
        //this.handleRemoveAll = this.handleRemoveAll.bind(this);
    //}

        render() {
        return (
            <div>
                {
                    this.props.options.map
                    (option => <Option key={option} optionText={option}/>)
                }
                <button
                    disabled={!this.props.hasOptions}
                    onClick={this.props.deleteOptions}>Remove All</button>
            </div>
        );
    }
};

class Option extends React.Component {
    render() {
        return (
            <div>
                <p>Option: {this.props.optionText}</p>
            </div>
        );
    }
};

class AddOptions extends React.Component {
    handleSubmit(e) {
        e.preventDefault();
        const value = e.target.elements.texto.value.trim();
        if (value) {
            alert(value);
            e.target.texto.value = '';
        }
    }

    render() {
        return (
            <div>
                <form onSubmit={this.handleSubmit}>
                    <input name='texto' type="text" placeholder="type a new option here" />
                    <button>Add it</button>
                </form>
            </div>
        );
    }
};

ReactDOM.render(<IndecisionApp />, document.getElementById('app'));
