const graphql = require('graphql');
const _ = require('lodash');

const Console = require('./../models/console');
const Game = require('./../models/game');

const {
    GraphQLNonNull,
    GraphQLObjectType,
    GraphQLString,
    GraphQLSchema,
    GraphQLID,
    GraphQLInt,
    GraphQLList
} = graphql;



const GameType = new GraphQLObjectType({
    name: 'Game',
    fields: () => ({
        id: { type: GraphQLID },
        name: { type: GraphQLString },
        genre: { type: GraphQLString },
        console: {
            type: ConsoleType,
            resolve(parent, args) {
                return Console.find( { id: parent.consoleId } );
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
                return Game.find({ consoleId: parent.id });
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
                return Game.findById(args.id);
            }
        },
        console: {
            type: ConsoleType,
            args: { id: { type: GraphQLID } },
            resolve(parent, args) {
                return Console.findById(args.id);
            }
        },
        games: {
            type: new GraphQLList(GameType),
            resolve(parent, args) {
                return Game.find({});
            }
        },
        consoles: {
            type: new GraphQLList(ConsoleType),
            resolve(parent, args) {
                return Console.find({});
            }
        }
    }
});

const Mutation = new GraphQLObjectType({
    name: 'Mutation',
    fields: {
        addGame: {
            type: GameType,
            args: {
                name: { type: GraphQLString },
                genre: { type: GraphQLString },
                consoleId: { type: GraphQLString }
            },
            resolve(parent, args) {
                const game = new Game({
                    name: new GraphQLNonNull(args.name),
                    genre: new GraphQLNonNull(args.genre),
                    consoleId: new GraphQLNonNull(args.consoleId)
                });
                return game.save();
            }
        },
        addConsole: {
            type: ConsoleType,
            args: {
                name: { type: new GraphQLNonNull(GraphQLString) },
                year: { type: GraphQLInt }
            },
            resolve(parent, args) {
                const console = new Console({
                    name: args.name,
                    year: args.year
                });
                return console.save();
            }
        }
    }

})

module.exports = new GraphQLSchema({
    query: RootQuery,
    mutation: Mutation
});
