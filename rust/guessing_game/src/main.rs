/* Tell rust we are going to use an external dependecy */
/* To know more about the rand crate run the command cargo doc --open */
extern crate rand;

/* The std::io library is here to let us bring the input type feature to the user */
use std::io;
use std::cmp::Ordering;
/* The 'Rng' defines methods that random number */
use rand::Rng;

fn main() {

    println!("Guess the number!");

    let max_rounds = 4;
    let mut rounds = 0;

    /* secret_number holds the random number returned from the gen_range function.
     * as you know already, secret_number is an immutable variable
     */

    let secrect_number = rand::thread_rng().gen_range(1, 101);
    println!("The secret code is: {}.", secrect_number);

    loop {

        match rounds.cmp(&max_rounds) {
            Ordering::Equal => {
                println!("You've have used all of your chances to guess the right value");
                break;
            },
            Ordering::Less => {
                rounds = rounds + 1
            },
            Ordering::Greater => continue,
        }

        /* let is how we create variables
         * but the thing is: let by itself will create an immutable value because we want the value
         * of guess to be changed while our software runs we must be explicit about it and the way
         * we do so is using mut.
         *
         * So by using let mut guess; We are telling the Rust compiler that we know this variable
         * will have its value changed in some point of our software. This gives the compiler a
         * better undastand of your software and because of that the compiler will be able to do a
         * better check for bugs and pitfalls.
         *
         * The '::' symbol indicates that 'new' is an associated function of the 'String' type
         *
         */

        let mut guess = String::new();

        println!("Please input your guess.");

        /* 'io::stdin() returns an instance of Stdin which is a type that represents a handle to
         * the standart input for the terminal
         *
         * Note that when we call read_line giving it a place in memory to save the String that the
         * user will type we use the `mut` symbol again.  That argument needs to be mutable so the
         * method can change the string's content by adding the user input to it
         *
         * The '&' just like in C idicates a reference
         *
         * |!| An important node is that just like variables, references are immutable by default!
         *
         * When 'read_line' is done it returns a 'Result' type. This 'Result' type has the 'expect'
         * function we call after the '.' symbol.  expect will take the return value and process
         * it.
         *
         * |Rust| If you by any means forget to call the except function the compiler will complain
         * which is just awesome!
         */

        io::stdin().read_line(&mut guess)
            .expect("Failed to read line");

        /* |!| Rust let us to shadow the previous value of guess with a new one It is often used in
         * situations in which you want to convert a value from one type to another type
         *
         * The trim method will get rid of any white spaces and the \n caused by pressing enter
         *
         * The except function is the one that will return the converted number. It will happen if
         * the trim function returns an 'ok ResutType'
         */

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        /* {} holds values. In this case, the guess value to be printed */

        println!("You guessed: {}", guess);

        match guess.cmp(&secrect_number) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break;
            },
        }

    }
}
