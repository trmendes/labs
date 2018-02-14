socket = io.connect();

socket.on('connect', () => {
	console.log('connected to the server');
});

socket.on('disconnect', () => {
	console.log('disconnected from the server');
});

socket.on('newMessage', (message) => {
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
            console.log('ack');
        });
});

let locationButton = jQuery('#send-location');
locationButton.on('click', function() {
    if (!navigator.geolocation) {
        return alert('geolocation not supported by your browser');
    }

    navigator.geolocation.getCurrentPosition(function(position) {
        let msg = {
            lat: position.coords.latitude,
            log: position.coords.longitude
        };

        socket.emit('createLocationMessage', createMsg('Client', 'Server',
            msg),
            function() {
                console.log('ack');
            });
    }
    , function () {
        alert('Unable to fetch location');
    });

});

let createMsg = (from, to, body) => {
    return {
        from,
        to,
        body
    };
};
