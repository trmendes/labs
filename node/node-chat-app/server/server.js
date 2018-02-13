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
        console.log(`${message.body}`);

        if (message.to === 'Server') {
            if (message.body === 'joined') {
                socket.broadcast.emit('newMessage', createMsg('server',
                    'Clients',
                    `New user ${message.from} joined the chat`));
            }
        }

        /* Socket.emit emits a message to a single connection */
        // socket.emit('newMessage', createMsg(`${message.to}`, `${message.from}`,
        //     `Got it ${message.from}!`));

        /* io.emit emits a broadcast message */
        // io.emit('newMessage', createMsg(`${message.to}`, `${message.from}`,
        //     `Got it ${message.from}!`));

        /* socket.broadcast.emit will broadcast a message to everyone bu the one
         * who sent the message
         */
        // socket.broadcast.emit('newMessage', message);
    });
});

let createMsg = (from, to, body) => {
    return {
        from,
        to,
        body,
        createdAt: new Date().getTime()
    }
};

const port = process.env.PORT || 3000;


/* Not using the app to listen
 * using the http server
 */
server.listen(port, () => {
    console.log(`http://localhost:${port}`);
});

