'use strict'

const mongoose = require('mongoose');

/* Will tell mongoose we want to use Promise */
mongoose.Promise = global.Promise;

mongoose.connect('mongodb://localhost:27017/TodoApp');

/* Create a model for the Todo collection */
let Todo = mongoose.model('Todo', {
    text: {
        type: String,
        required: true,
        minlength: 1,
        trim: true
    },
    completed: {
        type: Boolean,
        default: false
    },
    completedAt:{
        type: Number,
        default: null
    }
});

let User = mongoose.model('User', {
    email: {
        type: String,
        required: true,
        minlength: 1,
        trim: true
    }
});

/* Here we create a new document. Since none of the data is defined as
 * required we can go with the text property only for now
 */
// let secTodo = new Todo({
//     text: 'Learn how to cook',
//     completed: true,
//     completedAt: 123
// });

// secTodo.save().then((doc) => {
//     console.log("Saved todo: ", doc);
// }).catch((e) => {
//     console.log("Unable to save todo");
// });

let user = new User({
    email: "bla@bla.com"
});

user.save().then((doc) => {
    console.log("Saved user:", doc);
}).catch((e) => {
    console.log("Unable to save user");
});
