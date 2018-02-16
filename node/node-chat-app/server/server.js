const path = require('path');
const express = require('express');
const http = require('http');

const app = express();

/* Creating the public directory path */
const publicPath = path.join(__dirname, '..', 'public');

const socketIO = require('socket.io');
const server = http.createServer(app);

const { createMsg, createLocationMsg } = require('./utils/message');
const { isRealString } = require('./utils/validation');
const { Users } = require('./utils/users');

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

const users = new Users();

io.on('connection', (socket) => {
    socket.on('join', (params, callback) => {
        if (!isRealString(params.name) ||
            !isRealString(params.room)) {
            return callback('Name and room name are required');
        }

        let room = params.room.toLowerCase(params.room);

        if (users.addUser(socket.id, params.name, room) === undefined) {
            return callback(`${params.name} is already in use`);
        }

        /* The sockets.io lib has a way to 'tag' a connection */
        socket.join(room);

        io.to(room).emit('updateUserList',
            users.getUserList(room));

        socket.emit('newMessage', createMsg('Server',
            params.name,
            'Welcome to the chat app'));

        socket.broadcast.to(room).emit('newMessage', createMsg('Server',
            'Broadcast',
            `New user ${params.name} connected`));

        callback();
    });

    socket.on('createMessage', (message, callback) => {
        let user = users.getUser(socket.id);
        if (user) {
            io.to(user.room).emit('newMessage', createMsg(user.name,
                'Broadcast', message.body));
            callback('ACK');
        } else {
            callback('Invalid User');
        }
    });

    socket.on('createLocationMessage', (message, callback) => {
        let user = users.getUser(socket.id);
        if (user) {
            io.to(user.room).emit('newLocationMessage', createLocationMsg(
                'Server', 'Broadcast', message.body.lat, message.body.log));
            callback('ACK');
        } else {
            callback('Invalid User');
        }
    });

    socket.on('disconnect', () => {
        let user = users.delUser(socket.id);
        if (user) {
            io.to(user.room).emit('updateUserList',
                users.getUserList(user.room));
            io.to(user.room).emit('newMessage',
                createMsg('Server', 'Broadcast', `${user.name} has left`));
        }
    });
});

const port = process.env.PORT || 3000;

/* Not using the app to listen
 * using the http server
 */
server.listen(port, () => {
    console.log(`http://localhost:${port}`);
});

