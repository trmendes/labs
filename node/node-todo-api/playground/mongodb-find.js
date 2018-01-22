/* This creates a var call MongoClient pulling out of the lib
 * We do the same with ObjectID */
const { MongoClient, ObjectID } = require('mongodb');

MongoClient.connect('mongodb://localhost:27017/TodoApp', (err, client) => {
    if (err) {
        return console.log('Unable to connect to MongoDB server');
    }
    const db = client.db('TodoApp')
    console.log('Connected to MongoDB server');

   db.collection('Todos').find().count().then((count) => {
        console.log("# of Todos: ", count);
    }, (err) => {
        console.log("Unable to fetch todos: ", err);
    });

    db.collection('Todos').find({
        _id: new ObjectID('5a6615b762c30b7ba14538d3')
    }).toArray().then((docs) => {
        console.log("Todos");
        console.log(JSON.stringify(docs, null, 2));
    }, (err) => {
        console.log("Unable to fetch todos: ", err);
    });

    client.close();
});
