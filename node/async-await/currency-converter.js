const axios = require('axios');

const getExchangeRate = (from, to) => {
    return axios.get(`https://api.fixer.io/latest?base=${from}`).then((res) => {
        return res.data.rates[to];
    });
};

const getCountries = currencyCode => {
    return axios.get(
        `https://restcountries.eu/rest/v2/currency/${currencyCode}`).
        then(res => {
            return res.data.map(contry => contry.name);
        });
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
});

// convertCurrency('CAD', 'USD', 100).then(data => {
//     console.log(data);
// });

// getExchangeRate('USD', 'BRL').then(rate => {
//     console.log(rate);
// }).catch(e => console.log(e));

// getCountries('USD').then(countries => {
//     console.log(countries);
// }).catch(e => console.log(e));
