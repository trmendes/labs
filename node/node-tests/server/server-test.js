const request = require('supertest');
const expect = require('expect');

let app = require('./server').app;


describe('Server tests', () =>  {
    describe("GET /", () => {
        it('should return response', (done) => {
            /* a supertest function */
            request(app)
                .get('/')
                .expect(404)
                .expect((res) => {
                    expect(res.body).toInclude({
                        error: 'Page not found'
                    });
                })
                .end(done); /* call done */
        });
    });

    describe("GET /users", () => {

        it('should return my user object', (done) => {
            request(app)
                .get('/users')
                .expect(200)
                .expect((res) => {
                    expect(res.body).toInclude({
                        name: 'user 1',
                        age: 20
                    });
                })
                .end(done);
        });
    });
});
