fn main() {
    let numbers: [i32; 5] = [10, 20, 30, 40, 50];

    for number in numbers.iter() {
        println!("Number: {}", number);
    }
}