socket = io.connect();

socket.on('connect', () => {
	console.log('connected to the server');
});

socket.on('disconnect', () => {
	console.log('disconnected from the server');
});

socket.on('newMessage', (message) => {
    console.log(`${message.body}`);
});

socket.emit('createMessage', {
  from: 'Frank',
  text: 'Hi'
}, function (data) {
  console.log('Got it', data);
});

let createMsg = (from, to, body) => {
    return {
        from,
        to,
        body
    };
};
