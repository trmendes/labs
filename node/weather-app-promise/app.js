const yargs = require('yargs');
const axios = require('axios');
const fs = require('fs');

const key = require('./forecastkey');
const secretKey = key.getSecretKey();

const argv = yargs.options({
    a: {
        demand: false,
        alias: 'address',
        describe: 'Address to fetch weather for',
        /* to ALWAYS parse the arg as a string */
        string: true
    },
    s: {
        demand: false,
        alias: 'set_default_location',
        describe: 'Define a default location',
        string: true
    },
    d: {
        demand: false,
        alias: 'use_default_address',
        describe: 'Check the forecast using the default address',
        string: true
    }
})
    .help()
    .alias('help', 'h')
    .argv;


let address = '';

if (argv.s !== undefined) {
    let newDefaultAddress = {
        address: argv.s
    };
    fs.writeFileSync('default_location.json', JSON.stringify(newDefaultAddress));
    return;
}

if (argv.a !== undefined) {
    address = argv.a;
} else if (argv.d !== undefined) {
    try {
        let defaultAddress = JSON.parse(fs.readFileSync('default_location.json'));
        address = defaultAddress.address;
        if (address === undefined)
            throw new Error('error: Weird! We have a corrupet file. We are sorrry! Please, set a new default address using the -s option. Check --help for more info.');
    } catch (error) {
        console.warn(error.message);
        return;
    }
} else {
    console.warn('run the --help option to check how to use this app');
    return;
}

const encURI = encodeURIComponent(address);
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
