'use strict';

console.log('app.js  is running');

const appRoot = document.getElementById('app');

const template = <div><h1>This is JSX from app.js!...</h1><p>Cool!</p></div>;

const template2 = (
    <div>
        <h1>Zeh Silva</h1>
        <p>Age: 345</p>
        <p>Location: Nepal</p>
    </div>);

ReactDOM.render(template2, appRoot);
