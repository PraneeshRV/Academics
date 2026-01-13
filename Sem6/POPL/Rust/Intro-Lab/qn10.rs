// Define an enum to handle different types
enum Item {
    Int(i32),
    Float(f64),
    Text(String),
}

fn main() {
    let items = vec![
        Item::Int(42),
        Item::Float(3.14),
        Item::Text(String::from("Hello World")),
    ];

    for item in items {
        match item {
            Item::Int(i) => println!("Integer: {}", i),
            Item::Float(f) => println!("Float: {}", f),
            Item::Text(s) => println!("String: {}", s),
        }
    }
}