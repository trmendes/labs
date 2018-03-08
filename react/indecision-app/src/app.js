class IndecisionApp extends React.Component {
    constructor(props) {
        super(props);
        this.handleDeleteOptions = this.handleDeleteOptions.bind(this);
        this.handlePick = this.handlePick.bind(this);
        this.handleAddOption = this.handleAddOption.bind(this);
        this.handleDeleteOption = this.handleDeleteOption.bind(this);

        this.state = {
            options: props.options
        };
    }

    handlePick() {
        const idx = Math.floor(Math.random() * this.state.options.length);
        alert(this.state.options[idx]);
    }

    handleDeleteOptions() {
        this.setState(() => ({options: []}));
    }

    handleDeleteOption(option) {
        console.log(option);
        this.setState((prevState) => ({
            options: prevState.options.filter(opt => opt !== option)
        }));
    }

    handleAddOption(option) {

        if (!option) {
            return 'Enter a valid option';
        }

        if (this.state.options.indexOf(option) > -1) {
            return 'This option already extists';
        }

        this.setState((prevState) =>
            ({options: prevState.options.concat(option)}));

    }

    render() {
        const title = 'Indecision';
        const subtitle = 'Put your life in the hands of a computer!';

        return (
            <div>
                <Header subtitle={subtitle}/>
                <Action
                    hasOptions={this.state.options.length > 0}
                    pick={this.handlePick}
                />
                <Options
                    options={this.state.options}
                    hasOptions={this.state.options.length > 0}
                    deleteOptions={this.handleDeleteOptions}
                    deleteOption={this.handleDeleteOption}
                />
                <AddOptions
                    addOption={this.handleAddOption}
                />
                <User name='Andrew' age={27}/>
            </div>
        );
    };
};

IndecisionApp.defaultProps = {
    options: []
};

const Header = (props) => {
    return (
        <div>
            <h1>{props.title}</h1>
            {props.subtitle && <h2>{props.subtitle}</h2>}
        </div>
    );
};

Header.defaultProps = {
    title: 'Indecision'
};

const Action = (props) => {
    return (
        <div>
            <button
                disabled={!props.hasOptions}
                onClick={props.pick}>What Should I do?</button>
        </div>
    );
};

const Options = (props) => {
    return (
        <div>
            {
                props.options.map
                (option => <Option
                    key={option}
                    optionText={option}
                    deleteOption={props.deleteOption}
                />)
            }
            <button
                disabled={!props.hasOptions}
                onClick={props.deleteOptions}>Remove All</button>
        </div>
    );
};

const Option = (props) => {
    return (
        <div>
            <p>Option: {props.optionText}</p>
            <button onClick={
                (e) => {
                    props.deleteOption(props.optionText)
                }
            }>remove</button>
        </div>
    );
};

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

const User = (props) => {
    return (
        <div>
            <p>Name: {props.name}</p>
            <p>Age: {props.age}</p>
        </div>
    );
};

ReactDOM.render(<IndecisionApp />, document.getElementById('app'));
