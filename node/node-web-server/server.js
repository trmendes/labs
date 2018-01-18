const express = require('express');
const hbs = require('hbs');

let app = express();


app.set('view engine', 'hbs');

/* Setup a server that publish the public directory */
app.use(express.static(__dirname + '/public'));

/* Setup a handler (a router)
 *
 * What do we send back to the person who made the request */
app.get('/', (req, res) => {
    // res.send('<html><body><h1>Hello express</h1></body></html>');
    res.render('home.hbs',{
        pageTitle: 'Home Page',
        welcomeMessage: 'Welcome to my webpage',
        currentYear: new Date().getFullYear()
    });
});

app.get('/about', (req, res) => {
    res.render('about.hbs', {
        pageTitle: 'About Page',
        currentYear: new Date().getFullYear()
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
