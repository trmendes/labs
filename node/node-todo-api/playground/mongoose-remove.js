const {ObjectID} = require('mongodb');

const {mongoose} = require('./../server/db/mongoose');
const {Todo} = require('./../server/models/todo');
const {User} = require('./../server/models/user');

//Mongoose give us
//Todo.remove({}) -> ALL Todo.remove({someObj})

// Todo.remove({}).then((result)=> {
//     console.log(result);
// });
//
Todo.findByIdAndRemove('5a6a25d38e5f0f7b309e1102').then((result) => {
    console.log(result);
});

Todo.findOneAndRemove({text: "Todo #2"}).then((result) => {
    console.log(result);
});


