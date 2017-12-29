/* I'm using the same filter example but now using currying */

let village = [
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
let findIt =
    name =>
    specie =>
    val =>
    val.species === specie && val.name === name;

/* filter will loop trough each item of the array
 * and for each item it will pass the callback
 * function which will return true or false.
 * In case of returning true filter will keep that value
 * In case of returning false filter won't keep that value
 */
let dodo = village.filter(findIt("dodo")("dog"));

console.log(dodo);
//console.log("Dodo:");
//console.log(dodo);
