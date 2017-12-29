/* Reduce is there when map or filter does not match
 * your needs. It is your SUPER-LIST-TRANSFORMATION
*/

var cid = [
    { ammount: 220 },
    { ammount: 20 },
    { ammount: 120 },
    { ammount: 10000 },
    { ammount: 10 },
    { ammount: 0.5 },
    { ammount: 12 },
    { ammount: -20 }
];

var totalAmmount;

/* ------------------------------------------------------------------ */
/* SIMPLE EXAMPLE */

/* reduce receives and object that it is inicialized after
 * the callback function (2nd arg) and the interated item is the
 * second value of the callback function
 */
totalAmmount = cid.reduce(function(sum, val) {
    console.log("inside reduce val: " + val.ammount );
    console.log("inside reduce sum: " + sum );
    return sum + val.ammount;
}, 0);

console.log("first: " + totalAmmount);

/* Other way of doing it */
totalAmmount = cid.reduce((sum, val) => sum + val.ammount, 0);

console.log("second: " + totalAmmount);
/* ------------------------------------------------------------------ */
