const expect = require('expect');

const {Users} = require('./users');

describe('Users', () => {
    let users;
    beforeEach(() => {
        users = new Users();
        users.addUser(1, 'Mike', 'nodejs');
        users.addUser(2, 'Robert', 'nodejs');
        users.addUser(3, 'Fernanda', 'react');
    });

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

    it('should return names for the users list', () => {
        let userNamesNodeJS = users.getUserList('nodejs');
        let userNamesReact = users.getUserList('react');
        expect(userNamesNodeJS).toEqual(['Mike', 'Robert']);
        expect(userNamesReact).toEqual(['Fernanda']);
    });

    it('should remove a user using an id', () => {
        let lenAfterRemove = users.userList.length - 1;
        users.delUser(1);
        expect(lenAfterRemove).toBe(users.userList.length);
    });

    it('should not remove the user using an invalid id', () => {
        let originalLen = users.userList.length;
        users.delUser(200);
        expect(originalLen).toBe(users.userList.length);
    });

    it ('should return the user using an id', () => {
        let user = users.getUser(2);
        expect(user.socketId).toBe(2);
    });

    it ('should not return the user name for an invalid id', () => {
        let user = users.getUser(200);
        expect(user).toBeUndefined();
    });

    it ('should not allow 2 users with the same name', () => {
        let user = users.addUser(10, 'Mike', 'nodejs');
        expect(user).toBeUndefined();
        user = users.addUser(10, 'MikeTheSecond', 'nodejs');
        expect(user).not.toBeUndefined();
    });

    it ('should return all the available channels', () => {
        let channels = users.getChannels();
        expect(channels.length).toBe(users.userList.length);
    });
});
