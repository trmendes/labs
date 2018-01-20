/* Test cases */
const utils = require('./utils');
const expect = require('expect');

/* it is a function provided by mocha */
it('should add two numbers', () => {
    let res = utils.add(33,11);
    // if (res !== 44)
    //     throw new Error(`value not corret. Expected 44 but got ${res}`);
    expect(res)
        .toBe(44)
        .toBeA('number');

});

it ('should square a number', () => {
    let value = 3;
    let res = utils.square(value);
    // if (res !== 9)
    //     throw new Error(`but I've got squara(${value}) = ${res} when I should get 9`);
    expect(res)
        .toBe(9)
        .toBeA('number');;
});

it ('should excpect some values', () => {
    // expect(12).toNotBe(11);
    // Since they are not the same objects it will not work
    // expect({name: 'Rodrigo'}).toBe({name: 'Rodrigo'});
    expect([2,3,5]).toInclude(2);
    expect([2,3,5]).toExclude(1);
    expect({
        name: 'Andrew',
        age: 25,
        location: 'Philadelphia'
    })
    .toInclude({
        age: 25
    });
});

it ('should verify first and last names are set', () => {
    let user = {
        age: 25,
        location: 'Philadelphia'
    };
    let res = utils.setName(user, "Rodrigo Rodolfo");
    /* They should be equal because javascript passes objects as reference */
    expect(user).toEqual(res);
    expect(res).toInclude({
        firstName: 'Rodrigo',
        lastName: 'Rodolfo'
    });
});