socket = io.connect();

socket.on('connect', () => {
	console.log('connected to the server');
    socket.emit('createMessage', createMsg('Lake', 'Server', 'joined'));
});

socket.on('disconnect', () => {
	console.log('disconnected from the server');
});

socket.on('newMessage', (message) => {
    console.log(`${message.body}`);
});

let createMsg = (from, to, body) => {
    return {
        from,
        to,
        body
    };
};
