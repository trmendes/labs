'use strict';

console.log('app.js  is running');

const appRoot = document.getElementById('app');

let template = <h1>This is JSX from app.js!...</h1>;

ReactDOM.render(template, appRoot);
