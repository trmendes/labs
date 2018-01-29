'use strict';

const {User} = require('./../models/user');

let authenticate = (req, res, next) => {
    let token = req.header('x-auth');
    User.findByToken(token).then((user) => {
        if (!user) {
            /* Since it generate the same 401 I reject it and send the PC to
             * the catch block
             */
            return Promise.reject();
        }
        req.user = user;
        req.token = token;
        next(); /* Send it back to the routing who called it */
    }).catch(() => {
        /* Tell the browswer auth is mandatorie */
        res.status(401).send();
        /* We don't call next here because we don't want to the code inside
         * the routing to be executed
         */
    });
};

module.exports = {authenticate};
