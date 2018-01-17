const request = require('request');

let geoCodeAddress = (address) => {
    return new Promise((resolve, reject) => {
        const encURI = encodeURIComponent(address);
        request({
            url: `https://maps.googleapis.com/maps/api/geocode/json?address=${encURI}`,
            json: true
        }, (error, response, body) => {
            if (error != null)
                reject('Unable to connect to the server');
            else {
                if (body.status === 'OK') {
                    resolve({
                        address: body.results[0].formatted_address,
                        lat: body.results[0].geometry.location.lat,
                        lng: body.results[0].geometry.location.lng
                    });
                } else {
                    reject('Unable to find that address');
                }
            }
        });
    });
};

geoCodeAddress('19146').then((location) => {
    console.log(JSON.stringify(location, null, 2));
}, (errorMsg) => { console.log(errorMsg); } );
