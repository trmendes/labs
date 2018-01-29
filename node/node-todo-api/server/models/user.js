const mongoose = require('mongoose');
const validator = require('validator');
const jwt = require('jsonwebtoken');
const _ = require('lodash');

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
    }, 'abc123').toString();
    user.tokens.push({access, token});
    return user.save().then(() => {
        return token;
    });
};

/* This function must return a Promise */
userSchema.statics.findByToken = function(token) {
    let decoded = null;
    try {
        decoded = jwt.verify(token, 'abc123');
    } catch (e) {
        return Promise.reject();
    }

    return User.findOne({
        '_id': decoded._id,
        'tokens.token': token,
        'tokens.access': 'auth'
    });
};

let User = mongoose.model('User', userSchema);

module.exports = {User};
