'use strict';

import React from 'react';
import Option from './Option';

const Options = (props) => {
    return (
        <div>
            {
                props.options.map
                (option => <Option
                    key={option}
                    optionText={option}
                    deleteOption={props.deleteOption}
                />)
            }
            <button
                disabled={!props.hasOptions}
                onClick={props.deleteOptions}>Remove All</button>
        </div>
    );
};

export default Options;
