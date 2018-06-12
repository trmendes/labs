'use strict';

const mongoose = require('mongoose');
const { Schema } = mongoose;

mongoose.Promise = global.Promise;

const gameSchema = Schema({
    name: String,
    developer: String,
    released: Date
});
const Game = mongoose.model('Game', gameSchema);

const consoleSchema = Schema({
    name: String,
    manufacturer: String,
    released: Date,
    /* A console has N games */
    games: [{
        type: Schema.Types.ObjectId,
        ref: 'Game'
    }]
});
const Console = mongoose.model('Console', consoleSchema);


mongoose.connect('mongodb://localhost/nintendo').then(() => {
    console.info('Connected to the mongoDB');
    createData();
}).catch((e) => {
    console.error(`Unable to connect. Is it running?`);
    process.exit(1);
});

async function createData() {
    try {
        /* A new console */
        const nintendoClassic = new Console({
            name: 'Nintendo Classic',
            manufacturer: 'Nintendo',
            released: '1990'
        });

        const game1 = new Game({
            name: 'The Legend of Zelda: A Link to the Past',
            developer: 'Nintendo',
            released: new Date('1991')
        });
        const game2 = new Game({
            name: 'Contra III: The Alien Wars',
            developer: 'Konami',
            released: new Date('1992')
        });
        const game3 = new Game({
            name: 'F-Zero',
            developer: 'Nintendo',
            released: new Date('1990')
        });

        nintendoClassic.games.push(game1);
        nintendoClassic.games.push(game2);
        nintendoClassic.games.push(game3);

        await game1.save();
        await game2.save();
        await game3.save();
        await nintendoClassic.save();

        await findGame(nintendoClassic.id, game1.id);
        await checkIfGameIsPlayable(nintendoClassic.id, game1.id);
        await removeGame(nintendoClassic.id, game1.id);
        //await printAllGames();
        mongoose.disconnect();
    } catch (e) {
        console.log(e);
    }
}

const findGame = async (consoleId, gameId) => {
    try {
        console.log('Find a Game');
        const csl = await Console.findById(consoleId);
        const game = csl.games.find((game) => game.id === gameId);
        console.log(`Game: ${game}`);
    } catch (e) {
        console.log(e);
    }
};

const checkIfGameIsPlayable = async (consoleId, gameId) => {
    try {
        console.log('Check if you can play this game with this console');
        const csl = await Console.findById(consoleId);
        const res = (csl.games.indexOf(gameId) >= 0);
        console.log(`Can I play it?: ${res}`);
    } catch (e) {
        console.log(e);
    }
}

const removeGame = async (consoleId, gameId) => {
    try {
        console.log('Remove a game');
        const csl = await Console.findById(consoleId).populate('games');
        console.log(`Size before pull ${csl.games.length}`);
        const ret = await Console.update(
            { id: consoleId },
            { $pull: { id: gameId } }
        );
        await csl.save();
        console.log(`Size after pull ${csl.games.length}`);
    } catch (e) {
        console.log(e);
    }
};

const printAllGames = async () => {
    console.log('print game');
    const games = await Console.find({}).populate('games');
    games.forEach((game) => {
        console.log(game);
    });
};
