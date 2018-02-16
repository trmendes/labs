class Users {

    constructor() {
        this.userList = [];
    }

    addUser(socketId, name, room) {
        let user = {socketId, name, room};
        this.userList.push(user);
        return user;
    };

    delUser(id) {
        let user = this.getUser(id);
        let newUserList = this.userList.filter(user => user.socketId !== id);
        this.userList = newUserList;
        return user;
    };

    getUser(id) {
        return this.userList.filter(user => user.socketId === id)[0];
    };

    getUserList(room) {
        return this.userList.
            filter(user => user.room === room).
            map(user => user.name);
    };

};

module.exports = {Users}
