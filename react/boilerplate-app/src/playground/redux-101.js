import { createStore } from 'redux';

const store = createStore((prevState  = { count: 0 }, action) => {
    console.log('action: ', action);
    switch (action.type) {
        case 'INCREMENT':
            return {count: prevState.count + 1};
        case 'DECREMENT':
            return {count: prevState.count - 1};
        case 'RESET':
            return {count: 0};
        default:
            return prevState;
    }
});

console.log(store.getState());

store.dispatch({
    type: 'INCREMENT'
});
console.log(store.getState());

store.dispatch({
    type: 'RESET'
});
console.log(store.getState());

store.dispatch({
    type: 'DECREMENT'
});
console.log(store.getState());
