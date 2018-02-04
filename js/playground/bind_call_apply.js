let john = {
    name: 'John',
    age: 26,
    job: 'teacher',
    presentation: function(style, timeOfDay) {
        if (style === 'formal') {
            console.log('Good %s ladies and gentlemen!!!', timeOfDay);
            console.log('My name is %s and Im a %s and Im % ages old',
                this.name, this.job, this.age);
        } else {
            console.log('What\'s up!!!');
            console.log('My name is %s and Im a %s and Im % ages old',
                this.name, this.job, this.age);
        }
    }
};

let emely = {
    name: 'Emely',
    age: 35,
    job: 'designer'
};

john.presentation('formal', 'morning');
john.presentation('friendly', 'morning');

/* Method borrowing - CALL (this, args...)*/
john.presentation.call(emely, 'formal', 'morning');

// john.presentation.apply(emely, ['friendly', 'afternoon']);

/* The bind method will return a function */
let johnFriendly = john.presentation.bind(john, 'friendly');
let emyFormal = john.presentation.bind(emely, 'formal');
johnFriendly('night');
emyFormal('afternoon');

/* Currring */
/* It is a tecnic when we create a function based on another function with
 * pre-set values like we did with johnFriendly */
