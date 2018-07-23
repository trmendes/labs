const myMap = function(array, callback) {
    let array = [];
    for ( let idx = 0; idx < array.length; ++idx ) {
        array.push(callback(array[idx]), i, array);
    }
    return array;
}
