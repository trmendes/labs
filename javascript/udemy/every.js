const myEvery = (arr, callback) => {
    for (let idx = 0; idx < arr.length; ++idx) {
        if (!callback(arr[idx], idx, arr)) {
            return false;
        }
    }
    return true;
}
