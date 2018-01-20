/* Test cases */
const utils = require('./utils');

/* it is a function provided by mocha */
it('should add two numbers', () => {
    let res = utils.add(33,11);
    if (res !== 44)
        throw new Error(`value not corret. Expected 44 but got ${res}`);
});

it ('should square a number', () => {
    let value = 3;
    let res = utils.square(value);
    if (res !== 9)
        throw new Error(`but I've got squara(${value}) = ${res} when I should get 9`);
});
