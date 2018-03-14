import React from 'react';
import ReactDOM from 'react-dom';
import {BrowserRouter, Route, Switch, Link, NavLink}
from 'react-router-dom';
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
        Page not found - <Link to="/">Go Home</Link>
    </div>
);

const Header = () => (
    <header>
        <h1>Expensify</h1>
        <NavLink to="/" activeClassName="is-active" exact={true}>Dashboard</NavLink>
        <NavLink to="/create" activeClassName="is-active">Create Exp</NavLink>
        <NavLink to="/edit" activeClassName="is-active">Edit Exp</NavLink>
        <NavLink to="/help" activeClassName="is-active">Help</NavLink>
    </header>
);

const routes = (
    <BrowserRouter>
        <div>
            <Header />
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
        </div>
    </BrowserRouter>
);
ReactDOM.render(routes , document.getElementById('app'));
