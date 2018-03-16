import { createStore, combineReducers } from 'redux';
import uuid from 'uuid';

const demoState = {
    expenses: [{
        id: 'anId',
        description: 'Jan Rent',
        note: 'This was the final payment',
        amount: 54500, //cents
        createdAt: 0
    }],
    filters: {
        text: 'rent',
        sortBy: 'amount', // date or amount
        startData: undefined,
        endDate: undefined
    }
};

// REMOVE_EXPENSE
// EDIT_EXPENSE
// SET_TEXT_FILTER
// SORT_BY_DATE
// SORT_BY_AMOUNT
// SET_START_DATE
// SET_END_DATE

const addExpense =
    ( {description = '', note = '', amount = 0, createdAt = 0} = {} ) => (
        {
            type: 'ADD_EXPENSE',
            expense: {
                id: uuid(),
                description,
                note,
                amount,
                createdAt
            }
        });

const removeExpense = ({ id } = {}) => (
    {
        type: 'REMOVE_EXPENSE',
        id
    });

// Expenses Reducer

const expenseRecuderDefaultState = [];

const expenseReducer = (state = expenseRecuderDefaultState, action) => {
    console.log(action.type);
    switch (action.type) {
        case 'ADD_EXPENSE':
            return [...state, action.expense];
        case 'REMOVE_EXPENSE':
            return state.filter((exp) => exp.id !== action.id);
        default:
            return state;
    }
};

const filterReducerDefaultState = {
    text: '',
    sortBy: 'data', // date or amount
    startData: undefined,
    endDate: undefined
};

const filterReducer = (state = filterReducerDefaultState, action) => {
    switch (action.type) {
        default:
            return state;
    }
};

const store = createStore(
    combineReducers({
        expenses: expenseReducer,
        filter: filterReducer
    })
);

store.subscribe(() => console.log(store.getState()));

const rent = store.dispatch(addExpense({description: 'Rent', amount: 300}));
const coffee = store.dispatch(addExpense({description: 'Coffee', amount: 10}));
store.dispatch(removeExpense({ id: coffee.expense.id }));

console.log(store.getState());
