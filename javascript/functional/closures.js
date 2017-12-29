var me = "Bruce Wayne";

/* Javascript uses something called lexical scope. Means that every variable declareted ouside of the scope of a function is avaiable for that function */

/* javascript has support for closures. That means the function
 * will have access to the variables outside it's scope.
 * In the case. the greetMe function will not have a copy to
 * the var 'me' but direct access to it
 */

function greetMe() {
	console.log(me);
}

console.log(greetMe());

/* In essence, makeAdder is a function factory — it creates functions which can
 * add a specific value to their argument. In the above example we use our
 * function factory to create two new functions — one that adds 5 to its
 * argument, and one that adds 10. */
/* from:
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Closures
 */

function makeAdder(x) {
	return function(y) {
		return x + y;
	};
}

var add5 = makeAdder(5);
var add10 = makeAdder(10);

console.log(add5(2));  // 7
console.log(add10(2)); // 12

/* Emulating private methods with closures */

function emulatePrivate(){
	var privateCounter = 0;
	function changeBy(val) {
		privateCounter += val;
	}
	/* Return an object that have access to the function */
	return {
		increment: function() {
			changeBy(1);
		},
		decrement: function() {
			changeBy(-1);
		},
		value: function() {
			return privateCounter;
		}
	};
}

counter = emulatePrivate();

console.log(counter.value()); // logs 0
counter.increment();
counter.increment();
console.log(counter.value()); // logs 2
counter.decrement();
console.log(counter.value()); // logs 1
