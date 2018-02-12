const path = require('path');
const express = require('express');
const http = require('http');

const app = express();

/* Creating the public directory path */
const publicPath = path.join(__dirname, '..', 'public');

const socketIO = require('socket.io');
const server = http.createServer(app);

/* A middleware to take all requests to the public
 * directory
 */
app.use(express.static(publicPath));

/* We want to create an IO socket using
 * our http server
 */
/* This socketIO lib will give us a
 * script to use at the browser
 * we have access to it using the follow addr
 * localhost:port/socket.io/socket.io.js
 */
const io = socketIO(server);

io.on('connection', (socket) => {
    socket.on('disconnect', () => {
        console.log('The same client went away');
    });

    socket.on('createMessage', (message) => {
        console.log(`Got a message from ${message.from} to ${message.to}`);
        console.log(`It says: ${message.body}`);

        socket.emit('newMessage', createMsg(`${message.to}`, `${message.from}`,
            `Got it ${message.from}!`));
    });
});

let createMsg = (from, to, body) => {
    return {
        from,
        to,
        body: body + '! Over!',
        createdAt: new Date()
    }
};

const port = process.env.PORT || 3000;


/* Not using the app to listen
 * using the http server
 */
server.listen(port, () => {
    console.log(`http://localhost:${port}`);
});

