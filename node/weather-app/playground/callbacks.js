let getUser = (id, callback) => {
    let dummyUser = {
        id: id,
        username: 'Led'
    };

    /* Simulate a external callback where we have to wait for some to come */
    setTimeout(() => {
        callback(dummyUser);
    }, 3000);
};

getUser(1000, (user) => {
    console.log(user);
});
