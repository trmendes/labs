let asyncAdd = (a, b) => {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            if (typeof a === 'number' && typeof b === 'number')
                resolve(a + b);
            else
                reject('Args must be numbers');
        }, 1500);
    });
};

/* Catch is used to catch the reject from any chained promise */

asyncAdd(5, 2).then((success) => {
    console.log("First Promise Fulfill: ", success);
    return asyncAdd(success, '33');
}).then((suc) => {
    console.log("Second Promise Fulfill: ", suc);
}).catch((errorMsg) => {
    console.log("Error: ", errorMsg);
});

let somePromise = new Promise((resolve, reject) => {
    /* If the promise is fulfilled it is resolved */
    /* When Promise can't keep it's promise it is rejected */
    setTimeout(() => {
        //resolve('Hey, it worked!');
        reject('Unable to Fulfill promise');
    }, 2500);
});

somePromise.then((simpleMsgForNow) => {
    console.log('Promise fulfilled: ', simpleMsgForNow);
}, (errorMsg) => {
    console.log('Error: ', errorMsg);
});
