'use strict';

let env = process.env.NODE_ENV || 'development';

console.log('**** env: %s ****', env);

if (env === 'development' || env === 'test') {
    let config = require('./config.json');
    let envCfg = config[env];
    let cfgKeysArray = Object.keys(envCfg);

    cfgKeysArray.forEach((key) => {
        process.env[key] = envCfg[key];
    });
}

// if (env === 'development') {
//     process.env.PORT = 3000;
//     process.env.MONGODB_URI = 'mongodb://localhost:27017/TodoApp';
// } else if (env === 'test') {
//     process.env.PORT = 3000;
//     process.env.MONGODB_URI = 'mongodb://localhost:27017/TodoAppTest';
// }
//

