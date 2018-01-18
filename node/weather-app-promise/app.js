const yargs = require('yargs');
const axios = require('axios');

const key = require('./forecastkey');
const secretKey = key.getSecretKey();

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

const encURI = encodeURIComponent(argv.address);
let geocodeUrl = `https://maps.googleapis.com/maps/api/geocode/json?address=${encURI}`;

/* axios will return a Promise and as such we have to implement then and
 * catch
 */
console.time("axios promise");
axios.get(geocodeUrl)
    .then((response) => {

        /* If something goes wrong we throw an error and it takes our program
         * counter to the catch statement (catch.else)
         */
        if (response.data.status === 'ZERO_RESULTS')
            throw new Error('Unable to find that address');

        let lat = response.data.results[0].geometry.location.lat;
        let lng = response.data.results[0].geometry.location.lng;

        console.log("-----");
        console.log("Address: %s", response.data.results[0].formatted_address);

        let weatherUrl = `https://api.darksky.net/forecast/${secretKey}/${lat},${lng}`;

        return axios.get(weatherUrl);
    })
    .then((response) => {
        /* Hadle the returned promise from the first one */
        let temperature = response.data.currently.temperature;
        let apparentTemperature = response.data.currently.apparentTemperature;
        console.log("It's currently: %d and it feels like %d", temperature, apparentTemperature);
    })
    .catch((error) => {
        if (error.code === "ENOTFOUND") {
            console.log("Unable to connect to the API servers.");
        } else {
            console.log(error.message);
        }
        console.timeEnd("axios promise");
    });
