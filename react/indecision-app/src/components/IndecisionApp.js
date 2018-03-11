import React from 'react';

import AddOptions from './AddOptions';
import Header from './Header';
import Action from './Action';
import Options from './Options';

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

    componentDidMount() {
        console.log('Component Did Mount');
    }

    componentDidUpdate(prevProps, prevState) {
        console.log('Componet Did Update');
        console.log(prevProps);
        console.log(prevState);
    }

    componentWillUnmount() {
        console.log('Componet Will Unmount');
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
            </div>
        );
    };
};

IndecisionApp.defaultProps = {
    options: []
};

export default IndecisionApp;
