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
            },
            budget: 0,
            percentage: -1
        }
        /* Private */
        let Expense = function(id, desc, value) {
            this.id = id;
            this.desc = desc;
            this.value = value;
            this.percentage = -1;
        };

        Expense.prototype.calcPercentage = function(totalInc) {
            if (totalInc > 0) {
                this.percentage = Math.floor(
                    (this.value / totalInc) * 100);
            } else {
                this.percentage = -1;
            }
        };

        Expense.prototype.getPercentage = function() {
            return this.percentage;
        }

        /* Private */
        let Income = function(id, desc, value) {
            this.id = id;
            this.desc = desc;
            this.value = value;
        }
        let calculateTotal = function(type) {
            let sum = 0;
            data.allItens[type].forEach((element) => {
                sum += element.value;
            });
            data.total[type] = sum;
        };
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
            deleteItem: (type, id) => {
                let idxToRemove = -1;
                let ids = data.allItens[type].map((el, idx) => {
                    return el.id;
                });
                let idx = ids.indexOf(id);
                if (idx !== -1) {
                    data.allItens[type].splice(idx, 1);
                }
            },
            calculateBudget: () => {
                calculateTotal('exp');
                calculateTotal('inc');
                data.budget = data.total.inc - data.total.exp;
                if (data.total.inc > 0) {
                    data.percentage = Math.round(
                        (data.total.exp / data.total.inc) * 100);
                } else {
                    data.percentage = -1;
                }
            },
            calculatePercentages: () => {
                data.allItens.exp.forEach((el) => {
                    el.calcPercentage(data.total.inc);
                });
            },
            getPercentages: () => {
                return data.allItens.exp.map((el) => {
                    return el.getPercentage();
                });
            },
            getBudget: () => {
                return {
                    budget: data.budget,
                    totalInc: data.total.inc,
                    totalExp: data.total.exp,
                    percentage: data.percentage
                }
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
            expContainer: '.expenses__list',
            budgetLabel: '.budget__value',
            incLabel: '.budget__income--value',
            expLabel: '.budget__expenses--value',
            percLabel: '.budget__expenses--percentage',
            container: '.container',
            percentageLabel: '.item__percentage'
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
                    html = '<div class="item clearfix" id="inc-%id%"><div \
                    class="item__description">%desc%</div><div class="right \
                    clearfix"><div class="item__value">%value%</div><div \
                    class="item__delete"><button class="item__delete--btn"><i \
                    class="ion-ios-close-outline"></i></button></div></div></div>';
                    element = document.querySelector(DOMStr.incContainer);
                } else {
                    html = '<div class="item clearfix" id="exp-%id%"><div \
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
            deleteItem: (toDelete) => {
                let el = document.getElementById(toDelete);
                el.parentNode.removeChild(el);
            },
            clearFields: () => {
                let fields = document.querySelectorAll(DOMStr.inputDesc + ', '
                    + DOMStr.inputValue);
                fields.forEach((el) => {
                    el.value = '';
                });
                fields[0].focus();
            },
            displayBudget: (obj) => {
                document.querySelector(DOMStr.budgetLabel).textContent =
                    obj.budget;
                document.querySelector(DOMStr.incLabel).textContent =
                    obj.totalInc;
                document.querySelector(DOMStr.expLabel).textContent =
                    obj.totalExp;
                if (obj.percentage >= 0) {
                    document.querySelector(DOMStr.percLabel).textContent =
                        obj.percentage + '%';
                } else {
                    document.querySelector(DOMStr.percLabel).textContent =
                        '---';
                }
            },
            displayPercentages: (percentages) => {
                let fields;
                fields = document.querySelectorAll(DOMStr.percentageLabel).
                    value;
                fields.forEach((el, idx) => {
                    if (percentages[idx] > 0) {
                        el.textContent = percentages[idx] + '%';
                    } else {
                        el.textContent = '---';
                    }
                });
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

            let topLabelInit = {
                budget: 0,
                totalInc: 0,
                totalExp: 0,
                percentage: -1
            }
            UICtrl.displayBudget(topLabelInit);

            document.querySelector(DOMStr.inputBtn).addEventListener('click',
                ctrlAddItem);
            document.addEventListener('keypress', (event) => {
                if (event.charCode === 0) {
                    ctrlAddItem();
                }
            });

            document.querySelector(DOMStr.container).addEventListener('click',
                ctrlDeleteItem);

        };

        let updateBudget = () => {
            let budget;
            budgetCtrl.calculateBudget();
            budget = budgetCtrl.getBudget();
            UICtrl.displayBudget(budget);
        };

        let updatePercentages = () => {
            budgetCtrl.calculatePercentages();
            let percentages = budgetCtrl.getPercentages();
            console.log(percentages);
        };

        let ctrlDeleteItem = (event) => {
            /* SO UGLY */
            let itemID = event.target.parentNode.parentNode.parentNode.id;
            let splitID, type, id;

            if (itemID) {
                splitID = itemID.split('-');
                type = splitID[0];
                id = parseInt(splitID[1], 10);
                budgetCtrl.deleteItem(type, id);
                UICtrl.deleteItem(itemID);
                updateBudget();
                updatePercentages();
            }
        };

        /* Private */
        let ctrlAddItem = () => {
            let input = UICtrl.getInput();
            if (input.desc !== "" && !isNaN(input.value) &&
                input.value > 0) {
                let nItem = budgetCtrl.addItem(input.type, input.desc,
                    input.value);
                UICtrl.addListenItem(nItem, input.type);
                updateBudget();
                updatePercentages();
            }
            UICtrl.clearFields();
        };

        return {
            init: () => setupEventListeners()
        }
    }
)(budgetController, UIController);

controller.init();
