import { createStore } from 'redux';

const store = createStore((prevState  = { count: 0 }, action) => {
    console.log('action: ', action);
    switch (action.type) {
        case 'INCREMENT':
            const inc = typeof action.incrementBy === 'number' ? action.incrementBy : 1;
            return {count: prevState.count + inc};
        case 'DECREMENT':
            const dec = typeof action.decrementBy === 'number' ? action.decrementBy : 1;
            return {count: prevState.count - dec};
        case 'RESET':
            return {count: 0};
        default:
            return prevState;
    }
});

/* Will be called everytime the state changes */
const unsubiscribe = store.subscribe(() => {
    console.log(store.getState());
});

store.dispatch({
    type: 'INCREMENT',
    incrementBy: 5
});

/* From now on we have no notifications anymore */
//unsubiscribe();

store.dispatch({
    type: 'RESET'
});

store.dispatch({
    type: 'DECREMENT',
    decrementBy: 3
});

