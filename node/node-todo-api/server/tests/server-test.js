'use stric';

const expect = require('expect');
const request = require('supertest');
const {ObjectID} = require('mongodb');

const {app} = require('./../server');
const {Todo} = require('./../models/todo');
const {User} = require('./../models/user');
const {todos, populateTodos} = require('./../seed/seed');
const {users, populateUsers} = require('./../seed/seed');

beforeEach(populateUsers);
beforeEach(populateTodos);

describe('POST /todos', () => {
    it('should create a new todo', (done) => {
        let text = 'Test todo text';

        request(app)
            .post('/todos')
            .send({text})
            .expect(200)
            .expect((res) => {
                expect(res.body.text).toBe(text);
            })
            .end((err, res) => {
                if (err) {
                    return done(err);
                }

                Todo.find({text}).then((todos) => {
                    expect(todos.length).toBe(1);
                    expect(todos[0].text).toBe(text);
                    done();
                }).catch((e) => done(e));
            });
    });

    it('should not create todo with invalid body data', (done) => {
        request(app)
            .post('/todos')
            .send({})
            .expect(400)
            .end((err, res) => {
                if (err) {
                    return done(err);
                }

                Todo.find().then((todos) => {
                    expect(todos.length).toBe(2);
                    done();
                }).catch((e) => done(e));
            });
    });
});

describe('GET /todos', () => {
    it('should get all todos', (done) => {
        request(app)
            .get('/todos')
            .expect(200)
            .expect((res) => {
                expect(res.body.todos.length).toBe(2);
            })
            .end(done);
    });
});

describe('GET /todos/:id', () => {
    it('should return todo doc', (done) => {
        request(app)
            .get(`/todos/${todos[0]._id.toHexString()}`)
            .expect(200)
            .expect((res) => {
                expect(res.body.todo.text).toBe(todos[0].text);
            })
            .end(done);
    });

    it('should return 404 if todo not found', (done) => {
        let hexId = new ObjectID().toHexString();

        request(app)
            .get(`/todos/${hexId}`)
            .expect(404)
            .end(done);
    });

    it('should return 404 for non-object ids', (done) => {
        request(app)
            .get('/todos/123abc')
            .expect(404)
            .end(done);
    });
});

describe('DEL /todos/:id', () => {
    it('should remove one doc', (done) => {
        request(app)
            .delete(`/todos/${todos[1]._id.toHexString()}`)
            .expect(200)
            .expect((res) => {
                expect(res.body.text).toBe(todos[1].text);
            })
            .end((err) => {
                if (err) {
                    return done(err);
                }
                Todo.findById(todos[1]._id.toHexString()).then((todo) => {
                    expect(todo).toBe(null);
                    done();
                }).catch((e) => done(e));
            });
    });

    it('should return 404 if todo not found', (done) => {
        let hexId = new ObjectID().toHexString();
        request(app).
            delete(`/todos/${hexId}`).
            expect(404).
            end(done);
    });

    it('Should return 404 if ObjectId is invalid', (done) => {
        let id = 123;
        request(app).
            delete(`/todos/${id}`).
            expect(404).
            end(done);
    });
});

describe('PATCH /todos/:id', () => {
    it('should update the todo', (done) => {
        let hexId = todos[0]._id.toHexString();
        let text = 'This should be the new text';
        request(app).
            patch(`/todos/${hexId}`).
            send({
                completed: true,
                text
            }).
            expect(200).
            expect((res) => {
                expect(res.body.todo.text).toBe(text);
                expect(res.body.todo.completed).toBe(true);
            }).
            end(done);
    });

    it('should clear completedAt when todo is not completed', (done) => {
        let hexId = todos[1]._id.toHexString();
        let text = 'This should be the new text!!!';
        request(app).
            patch(`/todos/${hexId}`).
            send({
                completed: false,
                text
            }).
            expect(200).
            expect((res) => {
                expect(res.body.todo.text).toBe(text);
                expect(res.body.todo.completed).toBe(false);
                expect(res.body.todo.completedAt).toBe(null);
            }).
            end(done);
    });
});

describe('GET /users/me', () => {
    it('should return user if auth', (done) => {
        request(app).
            get('/users/me').
            set('x-auth', users[0].tokens[0].token).
            expect(200).
            expect((res) => {
                expect(res.body._id).toBe(users[0]._id.toHexString());
                expect(res.body.email).toBe(users[0].email);
            }).end(done);
    });

    it('should return a 401 if not auth', (done) => {
        request(app).
            get('/users/me').
            set('x-auth', '123').
            expect(401).
            expect((res) => {
                expect(res.body).toEqual({});
            }).
            end(done);
    });
});

describe('POST /users', () => {
    it('should create an user', (done) => {
        let email = 'user2@email.com';
        let password = 'easyPass1234';

        request(app).
            post('/users').
            send({email, password}).
            expect(200).
            expect((res) => {
                expect(res.headers['x-auth']).toBeTruthy();
                expect(res.body._id).toBeTruthy();
                expect(res.body.email).toBe(email);
            }).
            end((err) => {
                if (err) {
                    return done(err);
                }

                User.findOne({email}).then((user) => {
                    expect(user).toBeTruthy();
                    expect(user.password).not.toBe(password);
                    done();
                }).catch((e) => done());
            });
    });

    it('should return val errors if req is invalid', (done) => {
        let email = 'blablablathisisnotanemail';
        let password = '123';

        request(app).
            post('/users').
            send({email, password}).
            expect(400).
            end(done);
    });

    it('should not create a user if emai is in use', (done) => {
        request(app).
            post('/todos').
            send(users[0]).
            expect(400).
            end(done);
    });
});

describe('POST /users/login', () => {
    it('should login user and return auth token', (done) => {
        request(app).
            post('/users/login').
            send(users[1]).
            expect(200).
            expect((res) => {
                expect(res.headers['x-auth']).toBeTruthy();
            }).
            end((err, res) => {
                if (err) {
                    return done(err);
                }
                User.findById(users[1]._id).then((user) => {
                    // expect(user.tokens[0]).toInclude({
                    //     access: 'auth',
                    //     token: res.headers['x-auth']
                    // });
                    done();
                }).catch((e) => done(e));
            });
    });

    it('should reject invalid login', (done) => {
        request(app).
            post('/users/login').
            send({
                email: 'bla@bla.com',
                password: '123'
            }).
            expect(400).
            expect((res) => {
                expect(res.headers['x-auth']).not.toBeTruthy();
            }).
            end(done);
    });
});
