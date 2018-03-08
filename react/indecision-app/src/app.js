class IndecisionApp extends React.Component {
    render() {
        const title = 'Indecision';
        const subtitle = 'Put your life in the hands of a computer!';
        const options = ['one', 'two', 'five'];
        return (
            <div>
                <Header title={title} subtitle={subtitle}/>
                <Action />
                <Options options={options}/>
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
                <button>What Should I do?</button>
            </div>
        );
    }
};

class Options extends React.Component {
    render() {
        return (
            <div>
                {
                    this.props.options.map
                    (option => <Option key={option} optionText={option}/>)
                }
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
    render() {
        return (
            <div>
                <p>AddOptions Component here!</p>
            </div>
        );
    }
};

ReactDOM.render(<IndecisionApp />, document.getElementById('app'));
