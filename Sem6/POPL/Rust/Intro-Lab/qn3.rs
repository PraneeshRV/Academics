fn increment_counter(counter: &mut i32, amount: i32) {
    *counter += amount;
}

fn main() {
    let mut counter = 0;
    increment_counter(&mut counter, 5);
    println!("Counter is now: {}", counter);
}