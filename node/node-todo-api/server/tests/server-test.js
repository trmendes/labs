const expect = require('expect');
const request = require('supertest');
const {ObjectID} = require('mongodb');

const { app } = require('./../server');
const { Todo } = require('./../models/todo');

const todos = [{
    _id: new ObjectID(),
    text: "Todo #1"
},{
    _id: new ObjectID(),
    text: "Todo #2"
}];

/* It will run before each test case */
/* A lifecycle method from supertest */
beforeEach((done) => {
    Todo.remove({}) /* Wipe out our todos */
        .then(() => {
            return Todo.insertMany(todos); /* to return a promise */
        })
        .then(done());
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
                Todo.find({text}).then((todos) => {
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
            .post('/todos')
            .send({})
            .expect(404)
            .end((err, resp) => {
                Todo.find().then( (todos) => {
                    expect(todos.length).toBe(todos.length);
                    done();
                }).catch((e) => {done(e)});
            });
    });
});

describe('GET /todos', () => {
    it('should get all todos', (done) => {
        request(app)
            .get('/todos')
            .expect(200)
            .expect((res) => {
                expect(res.body.length).toNotBe(0);
            })
            .end(done());
    });
});

describe(`GET /todos/${todos[0]._id.toHexString()}`, () => {

    it('should return todo doc', (done) => {
        request(app)
            .get(`/todos/${todos[0]._id.toHexString()}`)
            .expect(200)
            .expect((res) => {
                expect(res.body.todo.text).toBe(todos[0].text);
            })
            .end(done);
    });

    it('should return a 404 if todo not found', (done) => {
        let id = new ObjectID().toHexString();
        request(app)
            .get(`/todos/${id}`)
            .expect(404)
            .end(done);
    });

    it('should return 404 for a non-object id', (done) => {
        request(app)
            .get('/todos/123')
            .expect(404)
            .end(done);
    });
});
