/* This creates a var call MongoClient pulling out of the lib
 * We do the same with ObjectID */
const { MongoClient, ObjectID } = require('mongodb');

MongoClient.connect('mongodb://localhost:27017/TodoApp', (err, client) => {
    if (err) {
        return console.log('Unable to connect to MongoDB server');
    }
    const db = client.db('TodoApp')
    console.log('Connected to MongoDB server');

    // db.collection('Todos').insertOne({
    //     text: 'Wash car',
    //     completed: false
    // }, (err, result) => {
    //     if (err) {
    //         return console.log('Unable to insert todo', err);
    //     }
    //     console.log(JSON.stringify(result.ops, undefined, 2));
    // });

    db.collection('Users').insertOne({
        name: "Zeh Algusto",
        age: 58,
        location: "Pai, Thailand"
    }, (err, res) => {
        if (err) {
            return console.log('Unable to insert todo', err);
        }
        console.log(JSON.stringify(res.ops, undefined, 2));
        /* Since ObjectID holds a timestamp using 4 bytes we can call this function
         * to print the Timestamp when this document was created
         */
        console.log(res.ops[0]._id.getTimestamp());
 });

       client.close();
});