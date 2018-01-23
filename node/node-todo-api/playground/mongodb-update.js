/* This creates a var call MongoClient pulling out of the lib
 * We do the same with ObjectID */
const { MongoClient, ObjectID } = require('mongodb');

MongoClient.connect('mongodb://localhost:27017/TodoApp', (err, client) => {
    if (err)
        return console.log('Unable to connect to MongoDB server');

    const db = client.db('TodoApp')
    console.log('Connected to MongoDB server');

    db.collection('Todos').findOneAndUpdate({
        _id: new ObjectID('5a6615b762c30b7ba14538d3')
    }, {
        $set: {
            completed: true
        }
    }, {
        returnOriginal: false
    })
    .then((result) => {
        console.log(result);
    });

    db.collection('Users').findOneAndUpdate({
        _id: new ObjectID('5a66169f1e56e50409a62b1d')
    }, {
        $set: {
            name: "Zeh Algusto Silva"
        },
        $inc: {
            age: 1
        }
    }, {
        returnOriginal: false
    })
    .then((result) => {
        console.log(result);
    });

    client.close();
});
