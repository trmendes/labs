import React from 'react';
import { connect } from 'react-redux';
import ExpenseListItem from './ExpenseListItem';
import selectExpenses from './../selectors/expenses';

const ExpenseList = (props) => (
    <div>
        <h1>{props.expenses.length}</h1>
        {props.expenses.map((exp) => {
            return <ExpenseListItem key={exp.id} {...exp} />;
        })}
    </div>
);

const mapStateToProps = (state) => {
    return {
        expenses: selectExpenses(state.expenses, state.filter)
    };
};

/* Connect componet */
const ConnectExpenseList = connect(mapStateToProps)(ExpenseList);

export default ConnectExpenseList;
