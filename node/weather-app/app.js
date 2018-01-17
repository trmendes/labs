const request = require('request');
const yargs = require('yargs');

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

console.log(argv);

const encAddress = encodeURIComponent(argv.address);

request({
    url: `https://maps.googleapis.com/maps/api/geocode/json?address=${encAddress}`,
    /* We tell the server that we rather work with json than other format
     * so the server can make our life easier and pack the response as a json
     */
    json: true
}, (error, response, body) => {
    /* the body is the return of the http request
     * could be a html, json, etc
     * in this specific casa we are getting a json as a response to our
     * request
     */

    /* response holds info about the request/server/response */

    /* error holds info if something goes wrong like a server not found,
     * internet is down, etc */

    if (error == null) {
        if (body.status === "OK") {
            let lat = body.results[0].geometry.location.lat;
            let lng = body.results[0].geometry.location.lng;
            console.log(`Address: ${body.results[0].formatted_address}`);
            console.log(`Lat    : ${lat}`);
            console.log(`Long   : ${lng}`);
        } else {
            console.log("Unable to find that address");
        }

    } else {
        console.log("Unable to connect to Google serves.");
    }
});
