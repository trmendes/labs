'use strict';

const privateSalting = 'anything here';
const {SHA256} = require('crypto-js');
const jwt = require('jsonwebtoken');
const bcrypt = require('bcrypt');

let pwd = 'password/password';

/* The bigger the number, the longer it takes, the harder it is to brute force
 * X = how many rounds to generate a salt */
bcrypt.genSalt(10, (err, salt) => {
    bcrypt.hash(pwd, salt, (err, hash) => {
        console.log(hash);
    });
});

let generatedHash = '$2a$10$jKlB9/B4vRrNOsuWZGyuP.SL.Rc7NIlWv5RzNciCBkr/y6kHtERZ2';

bcrypt.compare(pwd, generatedHash, (err, res) => {
    console.log(res);
});

return;

let msg = 'I am user number 3';
let hash = SHA256(msg).toString();
console.log('MSG : %s\nHASH: %s\n', msg, hash);

let data = {
    id: 4
};

let token = {
    data,
    hash: SHA256(JSON.stringify(data) + privateSalting)
};

console.log('Token: ', token.hash.toString());

let jwtToken = jwt.sign(data, privateSalting);
let jwtDecodedRes = jwt.verify(jwtToken, privateSalting);

console.log('JWT Token: ', jwtToken);
console.log('JWT Decod: ', jwtDecodedRes);
