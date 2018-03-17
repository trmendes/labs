const filterReducerDefaultState = {
    text: '',
    sortBy: 'data', // date or amount
    startData: undefined,
    endDate: undefined
};

export const filterReducer = (state = filterReducerDefaultState, action) => {
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
