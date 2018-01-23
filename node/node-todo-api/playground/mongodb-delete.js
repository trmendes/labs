/* This creates a var call MongoClient pulling out of the lib
 * We do the same with ObjectID */
const { MongoClient, ObjectID } = require('mongodb');

MongoClient.connect('mongodb://localhost:27017/TodoApp', (err, client) => {
    if (err)
        return console.log('Unable to connect to MongoDB server');

    const db = client.db('TodoApp')
    console.log('Connected to MongoDB server');

    //DeleteMany

    // db.collection('Todos').deleteMany({text: "Wash car 2"}).then((result) => console.log("Deleted: ", result));

    //DeleteOne - It will delete the first one the matches the creteria
    //db.collection('Todos').deleteOne({text: "Wash car2"}).then((result) => console.log(result));

    //FindOneAndDelete - It will return the object. Awesome for a UNDO option
    db.collection('Todos').findOneAndDelete({text: "Wash car3"}).then((result) => console.log(result));

    client.close();
});
