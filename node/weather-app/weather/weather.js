const request = require('request');
const key = require('./forecastkey');

const secretKey = key.getSecretKey();

let getWeatherFor = (lat, lng, callback) => {
    request({
        url: `https://api.darksky.net/forecast/${secretKey}/${lat},${lng}`,
        json: true
    }, (error, response, body) => {
        if (error == null) {
            if (body.hasOwnProperty('code')) {
                callback(body.error);
            } else {
                callback(null, {
                    temperature: ((body.currently.temperature - 32) * 5/9).toPrecision(2),
                    apparentTemperature: ((body.currently.apparentTemperature - 32) * 5/9).toPrecision(2)
                });
            }
        } else {
            callback('Unable to connect to the server');
        }
    })
};

module.exports = {
    getWeatherFor
};
