import React from 'react';
import ReactDOM from 'react-dom';
import {BrowserRouter, Route, Switch} from 'react-router-dom';
import 'normalize.css/normalize.css';
import './styles/styles.scss';

const expenseDashboardPage = () => (
    <div>
        This is from my Dashboard component
    </div>
);

const addExpensePage = () => (
    <div>
        This is from my addExpense component
    </div>
);

const editExpensePage = () => (
    <div>
        This is from my editExpense component
    </div>
);

const helpExpensePage = () => (
    <div>
        This is from my helpExpense component
    </div>
);

const notFoundPage = () => (
    <div>
        Page not found
    </div>
);

const routes = (
    <BrowserRouter>
        <Switch>
            <Route
                path="/"
                component={expenseDashboardPage}
                exact={true}
            />
            <Route
                path="/create"
                component={addExpensePage}
            />
            <Route
                path="/edit"
                component={editExpensePage}
            />
            <Route
                path="/help"
                component={helpExpensePage}
            />
            <Route
                component={notFoundPage}

            />
        </Switch>
    </BrowserRouter>
);
ReactDOM.render(routes , document.getElementById('app'));
