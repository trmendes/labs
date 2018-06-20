const graphql = require('graphql');
const _ = require('lodash');

const {
    GraphQLObjectType,
    GraphQLString,
    GraphQLSchema,
    GraphQLID,
    GraphQLInt,
    GraphQLList
} = graphql;

const games = [
    { name: 'Zelda', genre: 'Fantasy', id: '1', consoleId: '1' },
    { name: 'F-Zero', genre: 'Race', id: '2', consoleId: '1' },
    { name: 'Alex Kid', genre: 'Adventure', id: '3', consoleId: '2' }
];

const consoles = [
    { name: 'Nintendo 16', year: 1990, id: '1' },
    { name: 'Master System', yeard: 1991, id: '2' }
];

const GameType = new GraphQLObjectType({
    name: 'Game',
    fields: () => ({
        id: { type: GraphQLID },
        name: { type: GraphQLString },
        genre: { type: GraphQLString },
        console: {
            type: ConsoleType,
            resolve(parent, args) {
                return _.find(consoles, {id: parent.consoleId} );
            }
        }
    })
});

const ConsoleType = new GraphQLObjectType({
    name: 'Console',
    fields: () => ({
        id: { type: GraphQLID },
        name: { type: GraphQLString },
        year: { type: GraphQLInt },
        games: {
            type: new GraphQLList(GameType),
            resolve(parent, args) {
                return _.filter(games, { consoleId: parent.id });
            }
        }
    })
});

const RootQuery = new GraphQLObjectType({
    name: 'RootQueryType',
    fields: {
        game: {
            type: GameType,
            args: { id: { type: GraphQLID } },
            resolve(parent, args) {
                return _.find(games, { id: args.id });
            }
        },
        console: {
            type: ConsoleType,
            args: { id: { type: GraphQLID } },
            resolve(parent, args) {
                return _.find(consoles, { id: args.id });
            }
        },
        games: {
            type: new GraphQLList(GameType),
            resolve(parent, args) {
                return games;
            }
        },
        consoles: {
            type: new GraphQLList(ConsoleType),
            resolve(parent, args) {
                return consoles;
            }
        }
    }
});

module.exports = new GraphQLSchema({
    query: RootQuery
});
