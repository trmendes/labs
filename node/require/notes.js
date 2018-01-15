console.log("Starting notes.js");

let addNote = (title, body) => {
    console.log(`Adding note ${title} - ${body}`);
};

let getAll = () => {
    console.log("Listing all notes");
};

let getNote = (title) => {
    console.log(`Fetching node ${title}`);
}

let removeNote = (title) => {
    console.log(`Removing note ${title}`);
}

module.exports = {
    addNote,
    getAll,
    getNote,
    removeNote
};
