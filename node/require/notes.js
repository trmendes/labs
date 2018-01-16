console.log("Starting notes.js");

const fs = require('fs');

let fetchNotes = () => {
    try {
        let notesString = fs.readFileSync("notes-data.json");
        return JSON.parse(notesString);
    } catch (e) {
        return [];
    }
};

let saveNotes = (notes) => {
    fs.writeFileSync("notes-data.json", JSON.stringify(notes));
};

let logNote = (note) => {
    console.log(`---`);
    console.log(`Title: ${note.title}`);
    console.log(`Body : ${note.body}`);
};

let addNote = (title, body) => {
    let notes = fetchNotes();

    let duplicateNote = notes.filter((note) => note.title === title);

    if (duplicateNote.length === 0) {
        let note = { title, body };
        notes.push(note);
        saveNotes(notes);
        return note;
    } else {
        return undefined;
    }
};

let getAll = () => {
    console.log("Listing all notes");
    return fetchNotes();
};

let getNote = (title) => {
    let notes = fetchNotes();
    let note = notes.filter((note) => note.title === title);
    return note.pop();
}

let removeNote = (title) => {
    let notes = fetchNotes();
    let filteredNotes = notes.filter((note) => note.title !== title);
    saveNotes(filteredNotes);
    return (filteredNotes.length !== notes.length);
}

module.exports = {
    addNote,
    getAll,
    getNote,
    removeNote,
    logNote
};


