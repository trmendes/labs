import React from 'react';
import {BrowserRouter, Route, Switch} from 'react-router-dom';
import Header from './../components/Header';
import ExpenseDashboard from './../components/ExpenseDashboard';
import AddExpense from './../components/AddExpense';
import EditExpense from './../components/EditExpense';
import Help from './../components/Help';
import NotFound from './../components/NotFound';

const AppRouter = () => (
    <BrowserRouter>
        <div>
            <Header />
            <Switch>
                <Route
                    path="/"
                    component={ExpenseDashboard}
                    exact={true}
                />
                <Route
                    path="/create"
                    component={AddExpense}
                />
                <Route
                    path="/edit"
                    component={EditExpense}
                />
                <Route
                    path="/help"
                    component={Help}
                />
                <Route
                    component={NotFound}

                />
            </Switch>
        </div>
    </BrowserRouter>
);

export default AppRouter;
