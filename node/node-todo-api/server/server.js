let express = require("express");
let bodyParser = require("body-parser");
let {ObjectID} = require("mongodb");

let {Todo} = require("./models/todo");

let app = express();

app.use(bodyParser.json());

app.post("/todos", (req, res) => {
    let todo = new Todo({
        text: req.body.text
    });

    todo.save().then((doc) => {
        res.status(200).send(doc);
    }, (e) => {
        res.status(400).send(e);
    });
});

app.get("/todos", (req, res) => {
    Todo.find().then((todos) => {
        res.status(200).send({
            len: todos.length,
            todos
        });
    }, (e) => {
        res.status(400).send(e);
    });
});

app.get("/todos/:id", (req , res) => {
    let id = req.params.id;

    if (!ObjectID.isValid(id)) {
        return res.status(404).send();
    }

    Todo.findById(id).then((todo) => {
        if (!todo) {
            return res.status(404).send();
        }

        res.send({todo});
    }).catch(() => {
        res.status(400).send();
    });
});

app.delete("/todos/:id", (req, res) => {
    let id = req.params.id;
    if (!ObjectID.isValid(id)) {
        return res.status(404).send();
    }

    Todo.findByIdAndRemove(id).then((todo) => {
        if (!todo)
            return res.status(404).send();
        res.send({todo});
    });
});

app.listen(3000, () => {
    console.log("Started on port 3000");
});

module.exports = { app };
