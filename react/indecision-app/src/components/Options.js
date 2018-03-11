'use strict';

import React from 'react';

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
