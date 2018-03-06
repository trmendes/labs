'use strict';

console.log('app.js  is running');

const appRoot = document.getElementById('app');

const app = {
    title: 'Web page',
    subtitle: 'This is our first example using JSX'
};


let count = 0;

const addOne = () => {
    console.log('++ ', count);
    ++count;
};
const subOne = () => {
    console.log('-- ', count);
    --count;
};
const reset = () => {
    console.log('reset');
    count = 0;
};

/* class is a reserved world so we have
 * to use className
 * https://reactjs.org/docs/dom-elements.html
 */
const templateCounter = (
    <div>
        <h1>Count: {count}</h1>
        <button onClick={addOne}>+1</button>
        <button onClick={subOne}>-1</button>
        <button onClick={reset}>Reset</button>
    </div>
);


const template = (
    <div>
        <h1>{app.title.toUpperCase()}</h1>
        {app.subtitle && <p>{app.subtitle}</p>}
    </div>);

// {app.subtitle && <p>{app.subtitle}</p>}
/* if app.subtitle exists show <p>app.stubtitle</p>
 * else don't show anything
 */

ReactDOM.render(templateCounter, appRoot);
