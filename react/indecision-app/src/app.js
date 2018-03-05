'use strict';

console.log('app.js  is running');

const appRoot = document.getElementById('app');

let template = <div><h1>This is JSX from app.js!...</h1><p>Cool!</p></div>;

ReactDOM.render(template, appRoot);
