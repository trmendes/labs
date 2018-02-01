'use strict';

const mongoose = require('mongoose');
const validator = require('validator');
const jwt = require('jsonwebtoken');
const _ = require('lodash');
const bcrypt = require('bcrypt');

let userObj = {
    email: {
        type: String,
        required: true,
        trim: true,
        minlength: 1,
        unique: true,
        validate: {
            validator: validator.isEmail,
            message: '{$VALUE} is not a valid email'
        }
    },
    password: {
        type: String,
        required: true,
        minLength: 6
    },
    tokens: [{
        access: {
            type: String,
            required: true
        },
        token: {
            type: String,
            required: true
        }
    }]
};

/* Overwrite a method to limit what comes back to the clint */
let userSchema = new mongoose.Schema(userObj);

userSchema.methods.toJSON = function() {
    let userO = this.toObject();
    return _.pick(userO, ['_id', 'email']);
};

/* Since we need this we can't use arrow functions */
userSchema.methods.generateAuthToken = function() {
    let user = this;
    let access = 'auth';
    let token = jwt.sign({
        _id: user._id.toHexString(),
        access
    }, process.env.JWT_SECRET).toString();
    user.tokens.push({access, token});
    return user.save().then(() => {
        return token;
    });
};

userSchema.methods.removeToken = function(token) {
    /* Mongodb operators */
    let user = this;
    return user.update({
        $pull: {
            tokens: {
                token: token
            }
        }
    });
};

userSchema.statics.findByCredentials = function(email, password) {
    let user = this;
    return User.findOne({email}).then((user) => {
        if (!user) {
            return Promise.reject();
        }
        /* Since bcrypt does NOT suport Promise we return a new one */
        return new Promise((resolve, reject) => {
            bcrypt.compare(password, user.password, (err, res) => {
                if (res) {
                    resolve(user);
                } else {
                    reject();
                }
            });
        });
    });
};

/* This function must return a Promise */
userSchema.statics.findByToken = function(token) {
    let decoded = null;
    try {
        decoded = jwt.verify(token, process.env.JWT_SECRET);
    } catch (e) {
        return Promise.reject();
    }

    return User.findOne({
        '_id': decoded._id,
        'tokens.token': token,
        'tokens.access': 'auth'
    });
};

/* Before save to the database we want to do something with the data */
userSchema.pre('save', function(next) {
    let user = this;
    if (user.isModified('password')) {
        bcrypt.genSalt(10, (err, salt) => {
            bcrypt.hash(user.password, salt, (err, hash) => {
                user.password = hash;
                next();
            });
        });
    } else {
        next();
    }
});

let User = mongoose.model('User', userSchema);

module.exports = {User};
