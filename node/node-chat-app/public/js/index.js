socket = io.connect();

socket.on('connect', () => {
	console.log('connected to the server');
});

socket.on('disconnect', () => {
	console.log('disconnected from the server');
});

socket.on('newMessage', (message) => {
    console.log(`${message.body}`);
    let li = jQuery('<li></li>');
    li.text(`${message.from}: ${message.body}`);
    jQuery('#messages').append(li);
});

jQuery('#message-form').on('submit', function (event) {
    /* Prevent the page to refresh */
    event.preventDefault();
    let msg = jQuery('[name=message]').val();
    socket.emit('createMessage', createMsg('Client', 'Server', msg),
        function () {
        });
});

let createMsg = (from, to, body) => {
    return {
        from,
        to,
        body
    };
};
