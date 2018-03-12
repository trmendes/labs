'use strict';

import React from 'react';

const Header = (props) => (
    <div className="container">
        <div className="header">
            <h1 className="header__title">{props.title}</h1>
            {props.subtitle && <h2 className="header__subtitle">{props.subtitle}</h2>}
        </div>
    </div>
);

Header.defaultProps = {
    title: 'Indecision'
};

export default Header;
