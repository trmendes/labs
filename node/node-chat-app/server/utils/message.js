const moment = require('moment');

const date = moment();

let createMsg = (from, to, body) => {
    return {
        from,
        to,
        body,
        createdAt: date.valueOf()
    }
};

let createLocationMsg = (from, to, lat, log) => {
    return {
        from,
        to,
        url: `https://nominatim.openstreetmap.org/search?q=${lat},${log}`,
        createdAt: date.valueOf()
    };
};

module.exports = { createMsg, createLocationMsg };
