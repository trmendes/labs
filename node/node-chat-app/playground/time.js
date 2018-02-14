const moment = require('moment');
console.log(new Date().getTime());
console.log(new Date().getMonth());

/* Represents the current moment in time */
let date = moment();
console.log(date.format());
console.log(date.format('MMM'));
console.log(date.format('MMM YYYY'));
console.log(date.format('MMM Do, YYYY'));
date.add(7, 'days');
console.log('7 Days ahead: ' + date.format('MMM Do, YYYY'));
date.subtract(14, 'days');
console.log('7 Days behind: ' + date.format('MMM Do, YYYY'));
date.add(7, 'days');
console.log('Time now: ' + date.format('h:mm a'));
