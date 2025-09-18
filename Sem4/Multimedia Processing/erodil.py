import numpy as np

def generate_random_matrix():
    return np.random.randint(0, 2, (9, 9))

def apply_erosion(matrix, struct_elem):
    eroded = np.zeros_like(matrix)
    rows, cols = matrix.shape
    for i in range(1, rows - 1):
        for j in range(1, cols - 1):
            if np.all(matrix[i-1:i+2, j-1:j+2][struct_elem == 1] == 1):
                eroded[i, j] = 1
    return eroded

def apply_dilation(matrix, struct_elem):
    dilated = np.zeros_like(matrix)
    rows, cols = matrix.shape
    for i in range(1, rows - 1):
        for j in range(1, cols - 1):
            if np.any(matrix[i-1:i+2, j-1:j+2][struct_elem == 1] == 1):
                dilated[i, j] = 1
    return dilated

def main():
    matrix = generate_random_matrix()
    struct_elem = np.array([[0,1,0], [1,1,1], [0,1,0]])
    
    print("Original 9x9 Binary Matrix:")
    print(matrix)
    
    choice = input("Choose operation - Erosion (E) or Dilation (D): ").strip().upper()
    
    if choice == 'E':
        result = apply_erosion(matrix, struct_elem)
        print("\nEroded Matrix:")
    elif choice == 'D':
        result = apply_dilation(matrix, struct_elem)
        print("\nDilated Matrix:")
    else:
        print("Invalid choice! Exiting...")
        return
    
    print(result)
    
if __name__ == "__main__":
    main()
