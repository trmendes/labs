const path = require('path');
const express = require('express');
const http = require('http');

const app = express();

/* Creating the public directory path */
const publicPath = path.join(__dirname, '..', 'public');

const socketIO = require('socket.io');
const server = http.createServer(app);

const { createMsg, createLocationMsg } = require('./utils/message');

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
    console.log('New user connected');

    socket.emit('newMessage', createMsg('Server',
        'Client',
        'Welcome to the chat app'));

    socket.broadcast.emit('newMessage', createMsg('Server',
        'Client',
        `New user connected`));

    socket.on('createMessage', (message, callback) => {
        io.emit('newMessage', createMsg(message.from, message.to, message.body));
        callback('ACK');
    });

    socket.on('createLocationMessage', (message, callback) => {
        io.emit('newLocationMessage', createLocationMsg('Server', 'Client',
            message.body.lat,
            message.body.log));
        callback('ACK');
    });

    socket.on('disconnect', () => {
        console.log('The same client went away');
    });
});

const port = process.env.PORT || 3000;

/* Not using the app to listen
 * using the http server
 */
server.listen(port, () => {
    console.log(`http://localhost:${port}`);
});

