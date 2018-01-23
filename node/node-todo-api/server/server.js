'use strict'

const mongoose = require('mongoose');

/* Will tell mongoose we want to use Promise */
mongoose.Promise = global.Promise;

mongoose.connect('mongodb://localhost:27017/TodoApp');

/* Create a model for the Todo collection */
let Todo = mongoose.model('Todo', {
    text: {
        type: String
    },
    completed: {
        type: Boolean
    },
    completedAt:{
        type: Number
    }
});

let Note = mongoose.model('Note', {
    title: {
        type: String
    },
    text: {
        type: String
    }
});


/* Here we create a new document. Since none of the data is defined as
 * required we can go with the text property only for now
 */
let newTodo = new Todo({
    text: 'Cook Dinner'
});

let secTodo = new Todo({
    text: 'Learn how to cook',
    completed: true,
    completedAt: 123
});


/* Save the Document will send it to the MongoDB Collection */
// newTodo.save().then((doc) => {
//     console.log("Saved todo: ", doc);
// }).catch((e) => {
//     console.log("Unable to save todo");
// });

secTodo.save().then((doc) => {
    console.log("Saved todo: ", doc);
}).catch((e) => {
    console.log("Unable to save todo");
});

