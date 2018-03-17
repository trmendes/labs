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

const editExpense = (id, updates) => (
    {
        type: 'EDIT_EXPENSE',
        id,
        updates
    });

const setTextFilter = (text = '') => (
    {
        type: 'SET_TEXT_FILTER',
        text
    });

const sortByDate = () => (
    {
        type: 'SORT_BY_DATE'
    });

const sortByAmount = () => (
    {
        type: 'SORT_BY_AMOUNT'
    });

const setStartDate = (timestamp = 0) => (
    {
        type: 'SET_START_DATE',
        timestamp
    });

const setEndDate = (timestamp = 0) => (
    {
        type: 'SET_END_DATE',
        timestamp
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
        case 'EDIT_EXPENSE':
            return state.map((exp) => {
                if (exp.id === action.id) {
                    return {
                        ...exp,
                        ...action.updates
                    };
                }
                return exp;
            });
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
        case 'SET_TEXT_FILTER':
            return {
                ...state,
                text: action.text
            };
        case 'SORT_BY_DATE':
            return {
                ...state,
                sortBy: 'date'
            };
        case 'SORT_BY_AMOUNT':
            return {
                ...state,
                sortBy: 'amount'
            };
        case 'SET_START_DATE':
            return {
                ...state,
                startData: action.timestamp
            };
        case 'SET_END_DATE':
            return {
                ...state,
                endDate: action.timestamp
            };
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

const getVisibleExpenses = (expenses, filters) => {
    const { text, sortBy, startDate, endDate } = filters;
    return expenses.filter((exp) => {

        const startDateMatch = typeof exp.startDate !== 'number' ||
            exp.startData >= startDate;

        const endDateMath = typeof exp.endDate !== 'number' ||
            exp.endDate <= endDate;

        const textMatch = exp.description.toLowerCase().includes(
            text.toLowerCase());

        return startDateMatch && endDateMath && textMatch;
    }).sort((a, b) => {
        if (sortBy === 'date') {
            return b.createdAt - a.createdAt;
        } else (sortBy === 'amount') {
            return b.amount - a.amount;
        }
    });
};

store.subscribe(() => {
    const state = store.getState();
    const visibleExpenses = getVisibleExpenses(state.expenses, state.filter);
    console.log(visibleExpenses)
});

const rent = store.dispatch(addExpense({description: 'Rent', amount: 300}));
const coffee = store.dispatch(addExpense({description: 'Coffee', amount: 3}));

// store.dispatch(removeExpense({ id: rent.expense.id }));

// store.dispatch(editExpense(coffee.expense.id, { amount: 5 }));

store.dispatch(setTextFilter('rent'));
// store.dispatch(setTextFilter(''));

// store.dispatch(sortByAmount());
// store.dispatch(sortByDate());

// store.dispatch(setStartDate(125));
// store.dispatch(setStartDate());

// store.dispatch(setEndDate(1250));
// store.dispatch(setEndDate());

console.log(store.getState())
