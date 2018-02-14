socket = io.connect();

socket.on('connect', () => {
	console.log('connected to the server');
});

socket.on('disconnect', () => {
	console.log('disconnected from the server');
});

socket.on('newMessage', (message) => {
    let formattedTime = moment(message.createdAt).format('h:mm a');
    let li = jQuery('<li></li>');
    li.text(`${formattedTime} ${message.from}: ${message.body}`);
    jQuery('#messages').append(li);
});

socket.on('newLocationMessage', (message) => {
    let formattedTime = moment(message.createdAt).format('h:mm a');
    let li = jQuery('<li></li>');
    let a = jQuery('<a target="_blank">My current location</a>');
    a.attr('href', message.url);
    li.text(`${formattedTime} ${message.from}: `);
    li.append(a);
    jQuery('#messages').append(li);
});

jQuery('#message-form').on('submit', function (event) {
    /* Prevent the page to refresh */
    event.preventDefault();
    let msg = jQuery('[name=message]');
    socket.emit('createMessage', createMsg('Client', 'Server', msg.val()),
        function () {
            console.log('ack');
            msg.val('');
        });
});

let locationButton = jQuery('#send-location');
locationButton.on('click', function() {
    if (!navigator.geolocation) {
        return alert('geolocation not supported by your browser');
    }
    locationButton.attr('disabled', true);
    navigator.geolocation.getCurrentPosition(function(position) {
        let msg = {
            lat: position.coords.latitude,
            log: position.coords.longitude
        };

        socket.emit('createLocationMessage', createMsg('Client', 'Server',
            msg),
            function() {
                locationButton.removeAttr('disabled');
                console.log('ack');
            });
    }
    , function () {
        locationButton.removeAttr('disabled');
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
