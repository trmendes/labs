const expect = require('expect');

const { createMsg } = require('./message');

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
});
