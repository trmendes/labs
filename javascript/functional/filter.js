/* Use filter to filter the dogs */

var village = [
    { name: "rosimere", species: "human" },
    { name: "tim", species: "cat" },
    { name: "dodo", species: "dog" },
    { name: "marcelo", species: "human" },
    { name: "rafaela", species: "human" }
];

/* filter will loop trough each item of the array
 * and for each item it will pass the callback
 * function which will return true or false.
 * In case of returning true filter will keep that value
 * In case of returning false filter won't keep that value
 */
var dogs = village.filter(function(val) {
    return val.species === "dog";
});

console.log(dogs);
