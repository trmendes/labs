const request = require('supertest');

let app = require('./server').app;


it ('should return hello world response', (done) => {
    /* a supertest function */
    request(app)
    .get('/')
    .expect('Hello world')
    .end(done); /* call done */
});

