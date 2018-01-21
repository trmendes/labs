const expect = require('expect');

const rewire = require('rewire');

let app = rewire('./app');

describe('App', () => {

    let db = {
        saveUser: expect.createSpy()
    };

    app.__set__('db', db);

    it('should call the spy correctly', () => {
        let spy = expect.createSpy();
        spy('call with something');
        /* If the spy had be called expect will pass. otherwhise, it will fail
         * */
        expect(spy).toHaveBeenCalled('call with something');
    });


    it('should clal saveUser with user Object', () => {
        let email = "bla@bla.com";
        let password = "123abc";
        app.handleSignup(email, password);
        expect(db.saveUser).toHaveBeenCalledWith({email, password});
    });
});
