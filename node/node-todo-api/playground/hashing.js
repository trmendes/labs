'use strict';

const privateSalting = 'anything here';
const {SHA256} = require('crypto-js');
const jwt = require('jsonwebtoken');

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
