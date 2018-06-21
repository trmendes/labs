const mongoose = require('mongoose');
const { Schema } = mongoose;

const consoleSchema = new Schema({
    name: String,
    year: Number
});

module.exports = mongoose.model('Console', consoleSchema);
