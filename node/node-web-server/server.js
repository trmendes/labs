const express = require('express');

let app = express();

/* Setup a server that publish the public directory */
app.use(express.static(__dirname + '/public'));

/* Setup a handler (a router)
 *
 * What do we send back to the person who made the request */
app.get('/', (req, res) => {
    // res.send('<html><body><h1>Hello express</h1></body></html>');
    res.send({
        name: 'Andrew',
        likes: ['biking', 'running']
    });
});

app.get('/about', (req, res) => {
    res.send('About page');
});

app.get('/bad', (req, res) => {
    res.send({
        errorMessage: 'Testing errorMessage'
    });
});

app.listen(3000, () => {
    console.log('Console is up and running');
});
