const axios = require('axios');

const getExchangeRate = async (from, to) => {
    try {
        const res =  await axios.get(`https://api.fixer.io/latest?base=${from}`);
        const rate = res.data.rates[to];
        if (rate) {
            return rate;
        } else {
            throw new Error(`${to} is not supported`);
        }
    } catch(e) {
        throw new Error(`Unable to get the rates for ${from}`);
    }
};

const getCountries = async currencyCode => {
    try {
        const res = await axios.get(
            `https://restcountries.eu/rest/v2/currency/${currencyCode}`);
        return res.data.map(contry => contry.name);
    } catch(e) {
        throw new Error(`Unable to get contries that use ${currencyCode}`);
    }
};

const convertCurrency = (from, to, amount) => {
    let gCountries;
    return getCountries(to).then(countries => {
        gCountries = countries;
        return getExchangeRate(from, to);
    }).then(rate => {
        const exchangeAmount = amount * rate;
        return `${amount} ${from} is worth ${exchangeAmount} ${to}. ${to} can be used in the following countries: ${gCountries.join(', ')}`;
    });
};

/* the same as convertCurrency but using async-await */
const convertCurrencyAsyncAwait = async(from, to, amount) => {
    const countries = await getCountries(to);
    const rate = await getExchangeRate(from, to);
    const exchangeAmount = amount * rate;
    return `${amount} ${from} is worth ${exchangeAmount} ${to}. ${to} can be used in the following countries: ${countries.join(', ')}`;
};


convertCurrencyAsyncAwait('CAD', 'USD', 100).then(data => {
    console.log(data);
}).catch(e => console.log(e.message));

// convertCurrency('CAD', 'USD', 100).then(data => {
//     console.log(data);
// });

// getExchangeRate('USD', 'BRL').then(rate => {
//     console.log(rate);
// }).catch(e => console.log(e));

// getCountries('USD').then(countries => {
//     console.log(countries);
// }).catch(e => console.log(e));
