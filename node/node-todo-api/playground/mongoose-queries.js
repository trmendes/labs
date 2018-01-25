const {ObjectID} = require('mongodb');

const {mongoose} = require('./../server/db/mongoose');
const {Todo} = require('./../server/models/todo.js');

let useNotFoundID = true;
let useFakeID = true;
let id;

if (useNotFoundID)
    id = '5a69dcc3ffec333365946156';
else
    id = '5a69dcc3ffec333365946155';

if (useFakeID)
    id = '123';

if (!useFakeID) {
    /* Return all that documents that match the find clause - An array*/
    Todo.find({
        _id: id /* Because we are using mongoose we don't need to create a new
    ObjectID object. Mongoose will take case of that */
    }).then((todos) => {
        console.log(JSON.stringify(todos, null, 2));
    });

    /* Return only one */
    Todo.findOne({
        _id: id /* Because we are using mongoose we don't need to create a new
    ObjectID object. Mongoose will take case of that */
    }).then((todo) => {
        if (!todo)
            console.log("Id NOT found");
        else
            console.log(JSON.stringify(todo, null, 2))
    });
}

if (ObjectID.isValid(id))
    console.log("Valid ID");
else
    console.log("Invalid ID");


/* Find by ID */
Todo.findById(id).then((todo)=> {
    if (!todo)
        console.log("Id NOT found");
    else
        console.log(JSON.stringify(todo, null, 2))
})
.catch((err) => {
    console.log("FETCH BY ID ERROR");
});

/* All the docs are at the mongoose website
 * Section: QUERIES
 */
