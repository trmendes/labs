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
    };

    getUser(id) {
    };

    getUserList(room) {
        //        return this.userList.filter((el) => el->room === "root");
    };

};

module.exports = {Users}
