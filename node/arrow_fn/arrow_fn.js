let square = x => x * x;

console.log(square(9));

let user = {
    name: 'User',
    sayHi: () => {
        console.log(arguments); /* won't work */
        console.log(`Hi. I'm ${this.name}`); /* won't work */
        /* arrow functions do not have access to this or any argument you don't
         * specify */
    },
    sayHiAlt() {
        /* to solve it you have to use regular functions */
        console.log(arguments);
        console.log(`Hi. I'm ${this.name}`);
    }
};

user.sayHiAlt(1, 2, 3);
/* You gonna get some errors */
user.sayHi(1, 2, 3);

/* In general if you don't need this and arguments you should use arrow
 * functions otherwise go to regular functions */
