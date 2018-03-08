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
    handlePick() {
        alert('handlePick');
    }

    render() {
        return (
            <div>
                <button onClick={this.handlePick}>What Should I do?</button>
            </div>
        );
    }
};

class Options extends React.Component {
    handleRemoveAll() {
        alert('it is gone');
    }

    render() {
        return (
            <div>
                {
                    this.props.options.map
                    (option => <Option key={option} optionText={option}/>)
                }
                <button onClick={this.handleRemoveAll}>Remove All</button>
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
