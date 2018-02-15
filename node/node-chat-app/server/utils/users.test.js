const expect = require('expect');

const {Users} = require('./users');

describe('Users', () => {
    it('should add a new user', () => {
        let users = new Users();
        let newUser = {
            id: 123,
            name: 'Andrew',
            room: 'nodejs'
        };
        let ret = users.addUser(newUser.id, newUser.name, newUser.room);
        expect(users.userList).toEqual([ret]);
    });
});
