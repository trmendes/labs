const expect = require('expect');
const request = require('supertest');

const { app } = require('./../server');
const { Todo } = require('./../models/todo');

/* It will run before each test case */
/* A lifecycle method from supertest */
beforeEach((done) => {
    Todo.remove({}) /* Wipe out our todos */
    .then(() => {
        done();
    });
});

describe('POST /todos', () => {

    it('should create a new todo', (done) => {
        let text = 'text from the todo text';
        request(app)
            .post('/todos') /* SuperText lib */
            .send({text}) /* SuperText lib */
            .expect(200) /* Expect lib */
        /* Next - a custom expect call  */
            .expect((res) => {
                expect(res.body.text).toBe(text);
            })
        /* Check the data inside mongodb */
            .end((err, resp) => {
                if (err)
                    return done(err); /* If it fails stop it */

                /* Fetch to check if the todo is there or not */
                Todo.find().then((todos) => {
                    /* Since we always delete the db before the test
                     * we must have only one document there
                     * and it must be === text
                     */
                    expect(todos.length).toBe(1);
                    expect(todos[0].text).toBe(text);
                    done();
                }).catch((e) => { done(e) })
            });
    });

    it('should not create todo with invalid data', (done) => {
        request(app)
            .post({})
            .expect(404)
            .end((err, resp) => {
                Todo.find().then( (todos) => {
                    expect(todos.length).toBe(0);
                    done();
                }).catch((e) => {done(e)});
            });
    });
});
