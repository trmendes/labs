const expect = require('expect');
const request = require('supertest');

const { app } = require('./../server');
const { Todo } = require('./../models/todo');

/* It will run before each test case */
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
            .post('/todos')
            .send({text})
            .expect(200)
            .expect((res) => {
                expect(res.body.text).toBe(text);
            })
            .end((err, resp) => {
                if (err)
                    return done(err);
                Todo.find().then((todos) => {
                    expect(todos.length).toBe(1);
                    expect(todos[0].text).toBe(text);
                    done();
                }).catch((e) => { done(e) })
            });
    });
});
