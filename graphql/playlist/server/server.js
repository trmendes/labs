'use strict';

const express = require('express');
const graphqlHTTP = require('express-graphql');
const mongoose = require('mongoose');

const schema = require('./schema/schema');

const app = express();

mongoose.connect('mongodb://localhost:27017/graphql-playlist').then(() => {
    console.log('connected to mongodb');
}).catch(e => {
    console.log('mongodb is not running');
    process.exit(1);
});

app.use('/graphql', graphqlHTTP({
    schema,
    graphiql: true
}));

app.listen(4000, () => {
    console.log('Listening for requests -> http://localhost:4000');
});
