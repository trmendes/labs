/* A new struct to hold the rectangle values */
/* Rust have the functionality to print a struct using
 * Debug {:?} but we have to splict opt in
 */
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

fn main() {
    let rect1 = (30, 50);
    let rect2 = new_rectangle(30, 50);

    println!(
        "The are of the retangle is {} square pixels",
        area(rect1)
    );

    // When we call area_struct we borrow the rect2 reference to that function
    // The ownership of this struct still mine
    println!(
        "The are of the retangle is {} square pixels",
        area_struct(&rect2)
    );

    println!(
        "The are of the retangle is {} square pixels",
        rect2.area()
    );

    // When we call area_struct_b we pass the ownership of this variable to the function
    // In this case when the function is done the variable will be free and we can't use
    // it anymore
    println!(
        "The are of the retangle is {} square pixels",
        area_struct_b(rect2)
    );

    println!("Rect1: {:?}", rect1);

    println!("Rect1: {:#?}", rect1);
}

// with tuples
// in one hand we have only one argment
// but in the other hand the code becomes a bit
// hard to understand.
// the developer might ask: WTF .0 and .1 mean?
fn area(dimensions: (u32, u32)) -> u32 {
    println!("area");
    return dimensions.0 * dimensions.1;
}

fn new_rectangle(width: u32, height: u32) -> Rectangle {
    println!("new_rectangle");
    return Rectangle { width, height };
}

// with a normal struct - requesting varible to be borrowed
fn area_struct(retangle: &Rectangle) -> u32 {
    println!("area_struct");
    retangle.width * retangle.height
}

// with a normal struct - requesting the ownership of the variable
fn area_struct_b(retangle: Rectangle) -> u32 {
    println!("area_struct_b");
    retangle.width * retangle.height
}

// Methods 'are functions that belongs to a struct'
// The main reason for using methods: ORGANIZATION
// We should have everyhing we could do with a rectangle as methods
impl Rectangle {
    fn area(&self) -> u32 {
        println!("Rectangle.area()");
        self.width * self.height
    }
}


// Rust doesn’t have an equivalent to the -> operator; instead, Rust has a feature called automatic
// referencing and dereferencing. Calling methods is one of the few places in Rust that has this
// behavior.

// Here’s how it works: when you call a method with object.something(), Rust automatically adds in &,
// &mut, or * so object matches the signature of the method. In other words, the following are the
// same:


// p1.distance(&p2); (&p1).distance(&p2);
