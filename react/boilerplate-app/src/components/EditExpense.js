import React from 'react';

const EditExpense = (props) => (
    <div>
        This is from my editExpense component
        Edit expensive with ID {props.match.params.id}
    </div>
);

export default EditExpense;
