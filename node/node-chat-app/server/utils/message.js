let createMsg = (from, to, body) => {
    return {
        from,
        to,
        body,
        createdAt: new Date().getTime()
    }
};

module.exports = { createMsg };
