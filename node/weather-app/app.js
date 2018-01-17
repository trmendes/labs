const yargs = require('yargs');

const geocode = require('./geocode/geocode');
const weather = require('./weather/weather');

const argv = yargs.options({
    a: {
        demand: true,
        alias: 'address',
        describe: 'Address to fetch weather for',
        /* to ALWAYS parse the arg as a string */
        string: true
    }
})
    .help()
    .alias('help', 'h')
    .argv;


geocode.getAddressGeocode(argv.address, (errorMsg, results) => {
    if (errorMsg != null) {
        console.log(errorMsg);
    } else {
        console.log(results.address);
        weather.getWeatherFor(results.lat, results.lng, (errorMsg, resultsWeather) => {
            if (errorMsg != null)
                console.log(errorMsg);
            else {
                console.log(`It's currentily ${resultsWeather.temperature} but it feels like ${resultsWeather.apparentTemperature}`);
            }
        });
    }
});


