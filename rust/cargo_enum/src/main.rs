#[derive(Debug)]
enum IpAddrKind {
    V4,
    V6,
}

/* We can put whenever we want inside of an enum */
#[derive(Debug)]
enum IpAddr {
    V4(u8, u8, u8, u8),
    V6(String),
}

#[derive(Debug)]
struct IpAddrS {
    kind: IpAddrKind,
    address: String,
}

/* Another example of an enum */
#[derive(Debug)]
enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

impl Message {
    fn print(&self) {
        println!("{:?}", self);
    }
}

fn main() {
    let four = IpAddrKind::V4;
    let six = IpAddrKind::V6;
    let home_s = IpAddrS {
        kind: IpAddrKind::V4,
        address: String::from("127.0.0.1")
    };
    let loopback_s = IpAddrS {
        kind: IpAddrKind::V6,
        address: String::from("::1"),
    };
    println!("V4: {:?}", four);
    println!("V6: {:?}", six);
    println!("HOME: {:?}", home_s);
    println!("LOOPBACK: {:?}", loopback_s);

    let home = IpAddr::V4(127,0,0,1);
    let loopback = IpAddr::V6(String::from("::1"));

    println!("HOME: {:?}", home);
    println!("LOOPBACK: {:?}", loopback);

    let msg = Message::Quit;
    msg.print();
}
