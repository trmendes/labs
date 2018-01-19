const express = require('express');
const hbs = require('hbs');
const fs = require('fs');

let app = express();
hbs.registerPartials(__dirname + '/views/partials');

app.set('view engine', 'hbs');

/* Register a new middleware to log page call */
app.use((req, res, next) => {
    let now = new Date().toDateString();
    /* Check the express response dot to see what we have access to */
    let log = `${now}:  ${req.method} ${req.url}\n`; /* GET / */
    fs.appendFile('server.log', log, error => {
        if (error)
            console.log("Unable to append to server.log");
    });
    next();
});

/* A middleware to `block` our website while we still working on it */
app.use((req, res, next) => {
    res.render('maintenance.hbs');
});

/* Setup a server that publish the public directory */
app.use(express.static(__dirname + '/public'));

hbs.registerHelper('getCurrentYear', () => {
    return new Date().getFullYear();
});

hbs.registerHelper('screamIt', (text) => {
    return text.toUpperCase();
});

/* Setup a handler (a router)
 *
 * What do we send back to the person who made the request */
app.get('/', (req, res) => {
    // res.send('<html><body><h1>Hello express</h1></body></html>');
    res.render('home.hbs',{
        pageTitle: 'Home Page',
        welcomeMessage: 'Welcome to my webpage'
    });
});

app.get('/about', (req, res) => {
    res.render('about.hbs', {
        pageTitle: 'About Page'
    });
});

app.get('/bad', (req, res) => {
    res.send({
        errorMessage: 'Testing errorMessage'
    });
});

app.listen(3000, () => {
    console.log('Console is up and running');
});
