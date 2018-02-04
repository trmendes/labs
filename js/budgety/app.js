'use strict';

// AN IIFE make everything inside it PRIVATE

let budgetController = (
    () => {
        /*
         * Because of Clousers the publicTest function
         * will ALWAYS have access to the x and add
         */

        /* Private */
        let x = 23;

        /* Private */
        let add = (a) => {
            return x + a;
        }

        /* Public */
        return {
            publicTest: (b) => {
                return add(b);
            }
        }
    }
)();

let UIController = (
    () => {

    }
)();

let controller = (
    (budgetCtrl, UICtrl) => {
        let z = budgetCtrl.publicTest(10);
        return {
            publicMethod: () => {
                console.log(z);
            }
        }
    }
)(budgetController, UIController);

controller.publicMethod();
