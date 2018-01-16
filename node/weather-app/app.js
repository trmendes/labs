let request = require('request');

request({
    url: 'https://maps.googleapis.com/maps/api/geocode/json?address=av%20brasil',
    json: true
}, (error, response, body) => {
    console.log(body);
});
