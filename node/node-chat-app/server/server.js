const path = require('path');
const express = require('express');
const http = require('http');

const socketIO = require('socket.io');
const publicPath = path.join(__dirname, '..', 'public');
const app = express();
const port = process.env.PORT || 3000;
const server = http.createServer(app);
const io = socketIO(server);

app.use(express.static(publicPath));

server.listen(port, () => {
    console.log(`http://localhost:${port}`);
});

