/* HIGHER-ORDER-FUNTIONS */
/* A higher-order-function is a funtion
 * that take other function as arguments
 */

/* Use filter to filter the dogs */

var village = [
    { name: "rosimere", species: "human" },
    { name: "tim", species: "cat" },
    { name: "dodo", species: "dog" },
    { name: "marcelo", species: "human" },
    { name: "rafaela", species: "human" }
];

/* In javascript function ARE VALUES
 * and you can exploit it dividing your code into
 * small simple function and COMPOSE them together
 */
function isItADog(val) {
    return val.species === "dog";
}

/* filter will loop trough each item of the array
 * and for each item it will pass the callback
 * function which will return true or false.
 * In case of returning true filter will keep that value
 * In case of returning false filter won't keep that value
 */
var dogs = village.filter(isItADog);

console.log("Dogs:");
console.log(dogs);
