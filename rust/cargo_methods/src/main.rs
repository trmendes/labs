struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    // block - don't take self as a parameter
    fn new(width: u32, height: u32) -> Rectangle {
        Rectangle { width, height }
    }

    // method
    fn area(&self) -> u32 {
        self.width * self.height
    }

    // method
    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }
}

fn main() {
    let rect1 = Rectangle::new(30, 50);
    let rect2 = Rectangle::new(10, 40);
    let rect3 = Rectangle::new(60, 45);


    println!("Area from rect1: {}, rect2: {}, rect3: {}",
             rect1.area(),
             rect2.area(),
             rect3.area());
    println!("Can rect1 hold rect2? {}", rect1.can_hold(&rect2));
    println!("Can rect1 hold reac3? {}", rect1.can_hold(&rect3));
}
