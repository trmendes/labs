const request = require('request');

let getAddressGeocode = (address, callback) => {
    const encURI = encodeURIComponent(address);
    debugger;
    request({
        url: `https://maps.googleapis.com/maps/api/geocode/json?address=${encURI}`,
        json: true
    }, (error, response, body) => {
        if (error == null) {
            if (body.status === 'OK') {
                callback(null , {
                    address: body.results[0].formatted_address,
                    lat: body.results[0].geometry.location.lat,
                    lng: body.results[0].geometry.location.lng
                });
            } else {
                callback("Unable to find that address");
            }
        } else {
            callback("Unable to connect to the server.");
        }
    });
};

module.exports = {
    getAddressGeocode
};
