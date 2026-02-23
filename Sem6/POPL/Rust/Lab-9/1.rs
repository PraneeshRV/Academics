use std::fs::{File, OpenOptions};
use std::io::{self, BufRead, BufReader, Write};
use std::path::Path;
use std::fmt;

#[derive(Debug, Clone, PartialEq)]
struct Item {
    id: u32,
    name: String,
    price: f32,
    quantity: u32,
}

#[derive(Debug, PartialEq)]
enum OrderStatus {
    Completed(Item),
    OutOfStock,
    ItemNotFound,
    InvalidOrder,
}

#[derive(Debug)]
enum AppError {
    IoError(io::Error),
    ParseError(String),
    MissingFile(String),
}

impl fmt::Display for AppError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match *self {
            AppError::IoError(ref err) => write!(f, "IO Error: {}", err),
            AppError::ParseError(ref err) => write!(f, "Parse Error: {}", err),
            AppError::MissingFile(ref filename) => write!(f, "Missing File: {}", filename),
        }
    }
}

impl From<io::Error> for AppError {
    fn from(err: io::Error) -> AppError {
        AppError::IoError(err)
    }
}

fn read_inventory(filename: &str) -> Result<Vec<Item>, AppError> {
    if !Path::new(filename).exists() {
        return Err(AppError::MissingFile(filename.to_string()));
    }

    let file = File::open(filename)?;
    let reader = BufReader::new(file);
    let mut inventory = Vec::new();

    for (index, line) in reader.lines().enumerate() {
        let line = line?;
        let parts: Vec<&str> = line.split(',').collect();
        if parts.len() != 4 {
            log_error(format!("Line {}: Invalid format in inventory file: {}", index + 1, line))?;
            continue;
        }

        let id = parts[0].trim().parse::<u32>().map_err(|_| AppError::ParseError(format!("Line {}: Invalid ID", index + 1)))?;
        let name = parts[1].trim().to_string();
        let price = parts[2].trim().parse::<f32>().map_err(|_| AppError::ParseError(format!("Line {}: Invalid Price", index + 1)))?;
        let quantity = parts[3].trim().parse::<u32>().map_err(|_| AppError::ParseError(format!("Line {}: Invalid Quantity", index + 1)))?;

        inventory.push(Item { id, name, price, quantity });
    }

    Ok(inventory)
}

fn save_inventory(filename: &str, inventory: &Vec<Item>) -> Result<(), AppError> {
    let mut file = File::create(filename)?;
    for item in inventory {
        writeln!(file, "{},{},{},{}", item.id, item.name, item.price, item.quantity)?;
    }
    Ok(())
}

fn log_error(message: String) -> Result<(), AppError> {
    let mut file = OpenOptions::new()
        .create(true)
        .append(true)
        .open("errors.log")?;
    writeln!(file, "{}", message)?;
    Ok(())
}


fn process_one_line(inventory: &mut Vec<Item>, line: &str) -> Result<OrderStatus, AppError> {
    let parts: Vec<&str> = line.split(',').collect();
    if parts.len() != 2 {
        return Ok(OrderStatus::InvalidOrder);
    }
    
    let item_id = match parts[0].trim().parse::<u32>() {
        Ok(id) => id,
        Err(_) => return Ok(OrderStatus::InvalidOrder),
    };
    
    let qty_needed = match parts[1].trim().parse::<u32>() {
        Ok(qty) => qty,
        Err(_) => return Ok(OrderStatus::InvalidOrder),
    };

    if let Some(item) = inventory.iter_mut().find(|i| i.id == item_id) {
        if item.quantity >= qty_needed {
            item.quantity -= qty_needed;
            let mut bought_item = item.clone();
            bought_item.quantity = qty_needed;
            Ok(OrderStatus::Completed(bought_item))
        } else {
            Ok(OrderStatus::OutOfStock)
        }
    } else {
        Ok(OrderStatus::ItemNotFound)
    }
}

fn process_orders(inventory: &mut Vec<Item>, orders_file: &str) -> Result<(), AppError> {
    if !Path::new(orders_file).exists() {
        return Err(AppError::MissingFile(orders_file.to_string()));
    }

    let file = File::open(orders_file)?;
    let reader = BufReader::new(file);
    let mut bill_file = File::create("bill.txt")?;

    writeln!(bill_file, "{:<20} {:<10} {:<10} {:<10}", "Item Name", "Qty", "Cost", "Total")?;
    writeln!(bill_file, "{}", "-".repeat(55))?;

    let mut grand_total = 0.0;

    for (index, line) in reader.lines().enumerate() {
        let line_content = line?;
        
        match process_one_line(inventory, &line_content)? {
            OrderStatus::Completed(item) => {
                let cost = item.price * item.quantity as f32;
                grand_total += cost;
                writeln!(bill_file, "{:<20} {:<10} {:.2}      {:.2}", item.name, item.quantity, item.price, cost)?;
                println!("Order for item {} (qty: {}) processed successfully.", item.id, item.quantity);
            },
            OrderStatus::OutOfStock => {
                 let _ = log_error(format!("Order Line {}: Out of Stock - {}", index + 1, line_content));
                 println!("Order failed: Out of Stock.");
            },
            OrderStatus::ItemNotFound => {
                 let _ = log_error(format!("Order Line {}: Item Not Found - {}", index + 1, line_content));
                 println!("Order failed: Item Not Found.");
            },
            OrderStatus::InvalidOrder => {
                 let _ = log_error(format!("Line {}: Invalid order format - {}", index + 1, line_content));
            }
        }
    }
    
    writeln!(bill_file, "{}", "-".repeat(55))?;
    writeln!(bill_file, "{:<43} {:.2}", "Grand Total:", grand_total)?;

    Ok(())
}

fn main() {
    match read_inventory("inventory.txt") {
        Ok(mut inventory) => {
            println!("Inventory loaded successfully.");
            match process_orders(&mut inventory, "orders.txt") {
                Ok(_) => {
                    println!("Orders processed. Check bill.txt for details.");
                    if let Err(e) = save_inventory("inventory.txt", &inventory) {
                         eprintln!("Failed to save updated inventory: {}", e);
                    } else {
                         println!("Inventory updated and saved to inventory.txt.");
                    }
                },
                Err(e) => eprintln!("Error processing orders: {}", e),
            }
        },
        Err(e) => eprintln!("Error loading inventory: {}", e),
    }
}
