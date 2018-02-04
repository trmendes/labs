// first we define the object

let personProto = {
    calculateAge: function() {
        console.log(2018 - this.yearOfBirth);
    }
};

let john = Object.create(personProto);

john.name = 'John';
john.yearOfBirth = 1999;
john.job = 'teacher';

console.log(JSON.stringify(john, null, 2));
console.log(john.calculateAge());

let jane = Object.create(personProto, {
    name: { value: 'Jane' },
    yearOfBirth: { value: 1969 },
    job: { value: 'designer' }
});

console.log(JSON.stringify(jane, null, 2));
console.log(jane.calculateAge());
