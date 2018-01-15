console.log('Starting app...');

const fs = require('fs');
const os = require('os');
const notes = require('./notes.js');

const _ = require('lodash');

const user = os.userInfo('utf9');

 fs.appendFile('grettings.txt', `Hi ${user.username}! You are ${notes.age}!\n`, err => {
     if (err)
         console.log("error");
 });

let res = notes.addNote();
let resAdd = notes.add;

console.log(res);
console.log(resAdd(3, 4));

console.log(_.isString(true));
console.log(_.isString("String"));
console.log(_.isString('Is it?'));

let array = [3, 3, 3, 2, 2, 2, 1, 1, 0, 30, 459, 302, 20];
let filterArray = _.uniq(array);
console.log(filterArray);
