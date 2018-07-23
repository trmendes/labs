const mySome = (arr, callback) => {
    for (let idx = 0; idx < callback.length; ++ idx) {
        if (callback(arr[idx], idx, arr)) {
            return true;
        }
    }
    return false;
}
