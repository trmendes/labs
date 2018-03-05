'use strict';

console.log('app.js  is running');

const appRoot = document.getElementById('app');

const app = {
    title: 'Web page',
    subtitle: 'This is our first example using JSX'
};

const template = (
    <div>
        <h1>{app.title.toUpperCase()}</h1>
        {app.subtitle && <p>{app.subtitle}</p>}
    </div>);

// {app.subtitle && <p>{app.subtitle}</p>}
/* if app.subtitle exists show <p>app.stubtitle</p>
 * else don't show anything
 */

ReactDOM.render(template, appRoot);
