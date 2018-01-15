console.log('Starting app...');

const fs = require('fs');
const os = require('os');
const notes = require('./notes.js');

 const user = os.userInfo('utf9');

 fs.appendFile('grettings.txt', `Hi ${user.username}! You are ${notes.age}!\n`, err => {
     if (err)
         console.log("error");
 });

let res = notes.addNote();
let resAdd = notes.add;

console.log(res);
console.log(resAdd(3, 4));
