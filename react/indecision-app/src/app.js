'use strict';

console.log('app.js  is running');

const appRoot = document.getElementById('app');

const app = {
    title: 'Web page',
    subtitle: 'This is our first example using JSX',
    options: []
};

const onFormSubmit = (e) => {
    /* Stop the full page refresh */
    e.preventDefault();
    const option = e.target.elements.opicao.value;
    if (option) {
        app.options.push(option);
        e.target.opicao.value = '';
        console.log(app.options);
        renderApp();
    }
};

const removeAll = () => {
    app.options = [];
    renderApp();
};

let updateArray = () => {
    let key = 0;
        console.log(jsXOptions);
    return jsXOptions;
};

const renderApp = () => {
    const template = (
    <div>
        <h1>{app.title.toUpperCase()}</h1>
        {app.subtitle && <p>{app.subtitle}</p>}
        <p>{app.options.length > 0 ? 'Here are your options' : 'No Options'}</p>
        <p>Options counter: {app.options.length}</p>
        <ol>
            {
                app.options.map(el => <li key={el}>{el}</li>)
            }
        </ol>
        <form onSubmit={onFormSubmit}>
            <input type="text" name='opicao' placeholder="describe a new option"></input>
            <button>Add Option</button>
        </form>
        <button onClick={removeAll}>Remove All</button>
    </div>);
    ReactDOM.render(template, appRoot);
};

renderApp();
