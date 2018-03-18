import React from 'react';

import ExpenseList from './ExpenseList';
import ExpenseListFilter from './ExpenseListFilter';

const ExpenseDashboard = () => (
    <div>
        <ExpenseList />
        <ExpenseListFilter />
    </div>
);

export default ExpenseDashboard;
