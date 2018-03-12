import React from 'react';
import Modal from 'react-modal';

Modal.setAppElement('#app');

const OptionModal = (props) =>
    (
        <Modal
            isOpen={!!props.selectedOption}
            contentLabel="Selected Option"
            onRequestClose={props.closeAlert}>
            <h3>Selected Option</h3>
            {props.selectedOption && <p>{props.selectedOption}</p>}
            <button onClick={props.closeAlert}>Got it!</button>
        </Modal>
    );


export default OptionModal;
