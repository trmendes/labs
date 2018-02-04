'use strict';

// AN IIFE make everything inside it PRIVATE

/* ----------------------------------------------------------------------------
 * BUDGET CONTROLLER
 * ----------------------------------------------------------------------------
 */
let budgetController = (
    () => {
        /* Private */
        let data = {
            allItens: {
                exp: [],
                inc: []
            },
            total: {
                exp: 0,
                inc: 0
            }
        }
        /* Private */
        let Expense = function(id, desc, value) {
            this.id = id;
            this.desc = desc;
            this.value = value;
        };
        /* Private */
        let Income = function(id, desc, value) {
            this.id = id;
            this.desc = desc;
            this.value = value;
        }
        return {
            addItem: (type, des, val) => {
                let newItem;
                let id = 0;

                if (type === 'exp') {
                    if (data.allItens.exp.length > 0) {
                        id = data.allItens.exp[data.allItens.exp.length - 1].id
                            + 1;
                    }
                    newItem = new Expense(id, des, val);
                    data.allItens.exp.push(newItem);
                } else {
                    if (data.allItens.inc.length > 0) {
                        id = data.allItens.inc[data.allItens.inc.length - 1].id
                            + 1;
                    }
                    newItem = new Income(id, des, val);
                    data.allItens.inc.push(newItem);
                }
                return newItem;
            },
            testData: () => console.log(data)
        };
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
            console.log('adding...');
            budgetCtrl.addItem(input.type, input.desc, input.value);
            budgetCtrl.testData();
        };

        return {
            init: () => setupEventListeners()
        }
    }
)(budgetController, UIController);

controller.init();
