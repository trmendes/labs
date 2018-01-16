console.log('Starting app...');

const fs = require('fs');
const _ = require('lodash');


const  yarg_title_options = {
    describe: 'Title of note',
    demand: true,
    alias: 't'
};

const yarg_body_options = {
    describe: 'Body of note',
    demand: true,
    alias: 'b'
};

const argv = require('yargs')
    .command('add', 'Add a new note', {
        title: yarg_title_options,
        body: yarg_body_options
    })
    .command('list', 'List all notes')
    .command('read', 'Read a note', {
        title: yarg_title_options
    })
    .command('remove', 'Remove a note', {
        title: yarg_title_options
    })
    .help()
    .argv;

console.log("Yargs: ", argv);

const notesDb = require('./notes.js');

let command = argv._[0];

if (command === 'add') {
    if (notesDb.addNote(argv.title, argv.body) === undefined) {
        console.log("Fail: Duplicated note");
    } else {
        console.log("Success: Note created");
    }
} else if (command === 'list') {
    let notes = notesDb.getAll();
    notes.forEach((note) => {
        notesDb.logNote(note);
    });

} else if (command === 'read') {
    let note = notesDb.getNote(argv.title);
    (note !== undefined) ? notesDb.logNote(note) : console.log("Fail: Note not found");
} else if (command === 'remove') {
    console.log(`Removing note ${argv.title}`);
    let removed = notesDb.removeNote(argv.title);
    let msg = removed ? 'Success: Note was removed': 'Fail: Note note found';
    console.log(msg);
} else {
    console.log("Command not recognized");
}
