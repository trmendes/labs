const express = require('express');

let app = express();


app.get('/', (req, res) => {
    res.status(404).send({
        error: 'Page not found',
        name: 'Todo App v1.0'
    });
});

//GET  /users - array of users

app.get('/users', (req, res) => {
    let users = [
        {
            name: "user 1",
            age: 20
        },
        {
            name: "user 2",
            age: 30
        },
        {
            name: "user 3",
            age: 40
        }];

    res.status(200).send(users);
});

app.listen(3000);

module.exports.app = app;
