const myFilter = (arr, callback) => {
    let retArr = [];
    for (let idx = 0; idx < arr.length; ++idx) {
        if (callback(arr[idx], idx, arr)) {
            retArr.push(arr[idx]);
        }
    }
    return retArr;
}
