'use strict';

import React from 'react';

const Action = (props) => {
    return (
        <div>
            <button
                disabled={!props.hasOptions}
                onClick={props.pick}>What Should I do?</button>
        </div>
    );
};

export default Action;
