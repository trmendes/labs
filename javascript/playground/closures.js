// IIFE and Closures

function retirement(retirementAge) {
    let a = ' years left until retirement';

    return (yearOfBirh) => {
        let age = 2018 - yearOfBirh;
        /* We are using variables from a function one layer up */
        /* And this is a closure */
        console.log((retirementAge - age) + a);
    };
};

let germany = retirement(65);
let iceland = retirement(67);
let us = retirement(66);

us(1980);
iceland(1980);
germany(1980);


/* We could use closure to keep a variable private and protected from the
 * outer socpe */


let myPayCheck = (paycheck) => {
    return (name) => {
        console.log('discounts for %s: %d', name, paycheck * 0.2);
    };
};

let discA = myPayCheck(5000);
let discB = myPayCheck(6000);

let paycheck = 5000;
discA('john');
paycheck = 12000;
discB('anne');

/* The paycheck variable is protected inside of the myPayCheck function and it
 * is private to that function and its inner functions */

