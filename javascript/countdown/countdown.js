function countdown(time) {
    timeId = setInterval(() => {
        --time;

        if (time === 0) {
            console.log("Ring Ring Ring!!!");
            clearInterval(timeId);
        } else {
            console.log(time);
        }
    }, 1000);
}

countdown(3);
