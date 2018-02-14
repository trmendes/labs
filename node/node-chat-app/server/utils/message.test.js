const expect = require('expect');

const { createMsg, createLocationMsg } = require('./message');

describe('create Message',  () => {
    it('should generate correct message object', () => {
        const from = 'Tower';
        const to = 'Bridge';
        const msg = 'You are so strong';
        const message = createMsg(from, to, msg);
        expect(typeof message.createdAt).toBe('number');
        expect(message).toMatchObject({
            from: from,
            to: to,
            body: msg
        });
    });
    it('should generate a valid location message', () => {
        const from = 'Client';
        const to = 'Server';
        const lat = '13.364047';
        const log = '103.860313';
        const msg = createLocationMsg(from, to, lat, log);
        expect(typeof msg.createdAt).toBe('number');
        expect(msg).toMatchObject({
            from: from,
            to: to,
            url: `https://nominatim.openstreetmap.org/search?q=${lat},${log}`
        });
    });
});
