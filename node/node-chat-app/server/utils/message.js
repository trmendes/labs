let createMsg = (from, to, body) => {
    return {
        from,
        to,
        body,
        createdAt: new Date().getTime()
    }
};

let createLocationMsg = (from, to, lat, log) => {
    return {
        from,
        to,
        url: `https://nominatim.openstreetmap.org/search?q=${lat},${log}`,
        createdAt: new Date().getTime()
    };
};

module.exports = { createMsg, createLocationMsg };
