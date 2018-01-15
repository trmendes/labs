console.log("Starting notes.js");

/* We use exports to export functions out of our modules */
module.exports.addNote = () => {
    console.log("addNode");
    return "New note";
}

module.exports.add = (a, b) => {
    return a + b;
}
