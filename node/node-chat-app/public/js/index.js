socket = io.connect();

socket.on('connect', () => {
	console.log('connected to the server');
    socket.emit('newMessage', createMsg('Lake', 'Lake speaking!!'));
});

socket.on('disconnect', () => {
	console.log('disconnected from the server');
});

socket.on('newMessage', (message) => {
    console.log(`Got a new messagem from ${message.name}`);
    console.log(`It says: ${message.body}`);
});

let createMsg = (sender, body) => {
    return {
        name: sender,
        body: body + '! Over!';
    };
};
