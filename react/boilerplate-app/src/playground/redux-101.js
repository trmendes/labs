import { createStore } from 'redux';

const store = createStore((prevState  = { count: 0 }, action) => {
    console.log('action: ', action);
    switch (action.type) {
        case 'INCREMENT':
            return {count: prevState.count + action.incrementBy};
        case 'DECREMENT':
            return {count: prevState.count - action.decrementBy};
        case 'RESET':
            return {count: 0};
        case 'SET':
            return {count: action.count};
        default:
            return prevState;
    }
});

/* Action generators */

const increment = (value) => ({
    type: 'INCREMENT',
    incrementBy: typeof value === 'number' ? value : 1
});
const decrement = (value) => ({
    type: 'DECREMENT',
    decrementBy: typeof value === 'number' ? value : 1
});
const reset = () => ({ type: 'RESET' });
const set = value => ({ type: 'SET', count: value });

/* Will be called everytime the state changes */
const unsubiscribe = store.subscribe(() => {
    console.log(store.getState());
});

store.dispatch(increment(5));

/* From now on we have no notifications anymore */
//unsubiscribe();

store.dispatch(reset());

store.dispatch(decrement(3));

store.dispatch(set(101));

