socket = io.connect();

socket.on('connect', () => {
    console.log('connected to the server');
    let params = jQuery.deparam(window.location.search);
    socket.emit('join', params, function(error) {
        if (error) {
            alert(error);
            window.location.href = '/';
        } else {
            console.log('no error');
        }
    });
});

socket.on('disconnect', () => {
	console.log('disconnected from the server');
});

socket.on('newMessage', (message) => {
    let formattedTime = moment(message.createdAt).format('h:mm a');
    let template = jQuery('#message-template').html();
    let html = Mustache.render(template, {
        from: message.from,
        createdAt: formattedTime,
        body: message.body
    });
    jQuery('#messages').append(html);
});

socket.on('newLocationMessage', (message) => {
    let formattedTime = moment(message.createdAt).format('h:mm a');
    let template = jQuery('#location-template').html();
    let html = Mustache.render(template, {
        from: message.from,
        createdAt: formattedTime,
        url: message.url
    });
    jQuery('#messages').append(html);
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
