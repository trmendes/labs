/* Typescript is a subset of Javascript which means Javascript code is legal
 * inside of a TS file
 */

console.log('Hello world');

function hello(string: String) {
    console.log(`Hello ${string}`);
}

hello('moon');

/* because typescript is waiting for a string here the compiler will return
 * an error saying that a number is an invalid argument
 */
hello(1);
