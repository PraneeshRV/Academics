use std::f64::consts::PI;

fn calculate_circumference(diameter: f64) -> f64 {
    PI * diameter
}

fn main() {
    let diameter = 10.0;
    let circumference = calculate_circumference(diameter);
    println!("The circumference is: {:.2}", circumference);
}