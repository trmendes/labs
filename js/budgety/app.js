'use strict';

// AN IIFE make everything inside it PRIVATE

/* ----------------------------------------------------------------------------
 * BUDGET CONTROLLER
 * ----------------------------------------------------------------------------
 */
let budgetController = (
    () => {
        return;
    }
)();

/* ----------------------------------------------------------------------------
 * UI CONTROLLER
 * ----------------------------------------------------------------------------
 */
let UIController = (
    () => {

        let DOMStr = {
            inputType: '.add__type',
            inputDesc: '.add__description',
            inputValue: '.add__value',
            inputBtn: '.add__btn'
        }

        return {
            getInput: () => {
                return {
                    // type === inc = + || exp = -
                    type: document.querySelector(DOMStr.inputType).value,
                    desc: document.querySelector(DOMStr.inputDesc).value,
                    value: document.querySelector(DOMStr.inputValue).value
                }
            },
            getDOMString: () => DOMStr
        }
    }
)();

/* ----------------------------------------------------------------------------
 * GLOBAL APP CONTROLLER
 * ----------------------------------------------------------------------------
 */
let controller = (
    (budgetCtrl, UICtrl) => {
        /* Public */
        let setupEventListeners = () => {
            let DOMStr = UICtrl.getDOMString();
            document.querySelector(DOMStr.inputBtn).addEventListener('click',
                ctrlAddItem);
            document.addEventListener('keypress', (event) => {
                if (event.charCode === 0) {
                    ctrlAddItem();
                }
            });
        };
        /* Private */
        let ctrlAddItem = () => {
            let input = UICtrl.getInput();
            console.log(input);
        };

        return {
            init: () => setupEventListeners()
        }
    }
)(budgetController, UIController);

controller.init();
