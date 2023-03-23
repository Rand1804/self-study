fn main() {
    FtoC("65");
}

fn FtoC(fahrenheit: &str) {
    let fahrenheit: f32 = fahrenheit.trim().parse().expect("Please type a number!");
    let celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
    println!("{}°F is {}°C", fahrenheit, celsius);
}