import React from 'react';
import { connect } from 'react-redux';

const ExpenseList = (props) => (
    <div>
        <h1>{props.expenses.length}</h1>
        <h2>{props.filters.sortBy}</h2>
    </div>
);

const mapStateToProps = (state) => {
    return {
        expenses: state.expenses,
        filters: state.filter
    };
};

/* Connect componet */
const ConnectExpenseList = connect(mapStateToProps)(ExpenseList);

export default ConnectExpenseList;
