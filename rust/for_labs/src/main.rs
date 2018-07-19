fn main() {
    let celsius = fahrenheit_to_celsius(90.0);
    let fahrenheit = celsius_to_fahrenheit(celsius);
    println!("Celsius   : {}", celsius);
    println!("Fahrenheit: {}", fahrenheit);
    let fiabonacci = fiabonacci(9);
    println!("Fiabonacci: {}", fiabonacci);
}

fn fahrenheit_to_celsius(temperature: f32) -> f32 {
    let converted: f32 = (temperature - 32.0) * 5.0/9.0;
    converted
}

fn celsius_to_fahrenheit(temperature: f32) -> f32 {
    let converted: f32 = temperature * 9.0/5.0 + 32.0;
    converted
}

fn fiabonacci(position: i32) -> i32 {
    let mut f_a = 0;
    let mut f_b = 1;
    let mut f_tmp;
    for _idx in 0..position {
        f_tmp = f_a;
        f_a = f_tmp + f_b;
        f_b = f_tmp;
    }
    f_a
}
