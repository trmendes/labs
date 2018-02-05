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
            }
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
            inputBtn: '.add__btn',
            incContainer: '.income__list',
            expContainer: '.expenses__list'
        }

        return {
            getInput: () => {
                return {
                    // type === inc = + || exp = -
                    type: document.querySelector(DOMStr.inputType).value,
                    desc: document.querySelector(DOMStr.inputDesc).value,
                    value: parseFloat(document.querySelector(DOMStr.inputValue).value)
                }
            },
            addListenItem: (obj, type) => {
                let html, element;
                if (type === 'inc') {
                    html = '<div class="item clearfix" id="income-%id%"><div \
                    class="item__description">%desc%</div><div class="right \
                    clearfix"><div class="item__value">%value%</div><div \
                    class="item__delete"><button class="item__delete--btn"><i \
                    class="ion-ios-close-outline"></i></button></div></div></div>';
                    element = document.querySelector(DOMStr.incContainer);
                } else {
                    html = '<div class="item clearfix" id="expense-%id%"><div \
                    class="item__description">%desc%</div><div class="right \
                    clearfix"><div class="item__value">%value%</div><div \
                    class="item__percentage">21%</div><div \
                    class="item__delete"><button class="item__delete--btn"><i \
                    class="ion-ios-close-outline"></i></button></div></div></div>';
                    element = document.querySelector(DOMStr.expContainer);
                }
                html = html.replace('%id', obj.id);
                html = html.replace('%desc%', obj.desc);
                html = html.replace('%value%', obj.value);
                element.insertAdjacentHTML('beforeend', html);
            },
            clearFields: () => {
                let fields = document.querySelectorAll(DOMStr.inputDesc + ', '
                    + DOMStr.inputValue);
                fields.forEach((el) => {
                    el.value = '';
                });
                fields[0].focus();
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
        let updateBudget = () => {
            return;
        };
        /* Private */
        let ctrlAddItem = () => {
            let input = UICtrl.getInput();
            if (input.desc !== "" && !isNaN(input.value) &&
                input.value > 0) {
                let nItem = budgetCtrl.addItem(input.type, input.desc,
                    input.value);
                UICtrl.addListenItem(nItem, input.type);
            }
            UICtrl.clearFields();
        };

        return {
            init: () => setupEventListeners()
        }
    }
)(budgetController, UIController);

controller.init();
