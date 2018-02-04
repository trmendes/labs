let john = {
    name: 'John',
    yearOfBirth: 1990,
    job: 'teacher'
};

// Constructor
let Person = function(name, yearOfBirth, job) {
    this.name = name;
    this.yearOfBirth = yearOfBirth;
    this.job = job;
    this.haveANewJob = function(job) {
        this.job = job;
    };
};

// The method is not anymore in the constructor but we can still use
// because it is at it's prototype

Person.prototype.calculateAge = function() {
    console.log('%s [%s] - Year of Birth: %d', this.name, this.job,
        this.yearOfBirth);
};

// Instanciation
// John is an instance of Person
let newJohn = new Person('John', 1990, 'teacher');

// So when we use the new operator
// 1 - whe get an EMPTY object
// 2 - calling the constructor we set the properties
// ** The new operator creates an EMPTY object and makes newJohn points to this
// new empty object in memory

newJohn.haveANewJob('dancer');
newJohn.calculateAge();

let jane = new Person('Jane', 1999, 'designer');

jane.calculateAge();
