/* Just like filter a map is a higher-order-function
 * and also like filter it goes trough all the array
 * but unlike filter it transform the data */

var village = [
    { name: "rosimere", species: "human" },
    { name: "tim", species: "cat" },
    { name: "dodo", species: "dog" },
    { name: "marcelo", species: "human" },
    { name: "rafaela", species: "human" }
];

/* Map expects the callback function to return a transformed
 * data that it will use to put in the new array.
 */
function getInfo(val) {
    return val.name + " is a " + val.species;
}

var info = village.map(getInfo);

/* We could use arrow functions which is short way of
 * writing a new function
*/
var names = village.map((val) => { return val.name });

/* If your logic is as short as the one above your could
 * also do something like this:
 */
var species = village.map((val) => val.species );

console.log("Info:");
console.log(info);
console.log("Names:");
console.log(names);
console.log("Species:");
console.log(species);
