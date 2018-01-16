// let obj = {
//     name: 'Rodrigo'
// };

// let stringObj = JSON.stringify(obj);

// console.log(typeof stringObj);
// console.log(stringObj);

// let person = '{"name": "Rodrigo", "age": 345}';
// /* person is a string so I can't access the name or the age like in a object */
// let personObj = JSON.parse(person);

// console.log(typeof personObj);
// console.log(personObj);

const fs = require('fs');

let originalNote = {
    title: 'Some title',
    body: 'Some body'
};

originalNoteString = JSON.stringify(originalNote);
fs.writeFileSync('notes.json', originalNoteString);

let nodeString = fs.readFileSync('notes.json');

let noteObj = JSON.parse(nodeString);

console.log(typeof noteObj);
console.log(noteObj.title);
