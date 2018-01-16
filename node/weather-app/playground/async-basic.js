console.log('Starting app');

/* We setup it to run but the callback will be fired after 2s
 */
setTimeout( () => {
    console.log('Inside of callback');
}, 2000);

setTimeout( () => {
    console.log('inside of the second callback (0s)');
}, 0);

/* We setup a callback to be running 0s latter
 * it will start couting after the last call is made
 * because of the call stack.
 * So this msg '...second...' will appear 0 seconds after
 * 'finishing app'
/*

/* When we call setTimeout we register it at the node API that
 * starts the couting down */

/* When the couting down finish the callback will be moved to the
 * callback queue that holds all the callbacks that are ready to be
 * executed
 */

/* The callback queue will be checked ONLY when there is nothing at the main
 * call stack.
 */

/* The event loop is the one responsable to check it and it can only run one
 * function at time */

/* When the call stack is empty event loop will check the callback queue to
 * check if there are any functions to execute and if there are it will be
 * the first one will be moved to the call stack */

/* This will run until callstack and callback queue are not empty */

/* The app still running and the callback will run 2s after */
console.log('Finishing app');

/* When we fetch data from any webserver we have to wait it to come. Meanwhile
 * our app still doing other things */

