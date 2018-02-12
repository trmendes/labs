socket = io.connect();

socket.on('connect', () => {
	console.log('connected to the server');
    socket.emit('createMessage', createMsg('Lake', 'Tower', 'Lake speaking!'));
});

socket.on('disconnect', () => {
	console.log('disconnected from the server');
});

socket.on('newMessage', (message) => {
    console.log(`Got a new messagem from ${message.from} to ${message.to}`);
    console.log(`It says: ${message.body}`);
});

let createMsg = (from, to, body) => {
    return {
        from,
        to,
        body: body + '! Over!'
    };
};
