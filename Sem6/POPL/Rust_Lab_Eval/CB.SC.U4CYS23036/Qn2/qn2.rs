//Write a Rust Program that rotates and array left by k positions using loops and temporary storage. The program must work for any integer array.

fn rotate_left(arr: &[i32], k: usize) -> Vec<i32> {
    let x = arr.len();
    let mut array: Vec<i32> = arr.to_vec();
    let mut i = 0;
    let mut temp;
    while i < k {
        temp = array[0];
        let mut j = 0;
        while j < x - 1 {
            array[j] = array[j + 1];
            j += 1;
        }
        array[x - 1] = temp;
        i += 1;
    }
    array
}

fn main() {
    let arr: [i32; 10] = [-5, -4, -3, 2, 1, -1, -2, 10, 11, 7];
    println!("Rotated array {:?}", rotate_left(&arr, 3));
}