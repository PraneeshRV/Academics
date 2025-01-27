interface Matrix {
    void diagonalsMinMax(int[][] matrix);
}
class Main implements Matrix {
    @Override
    public void diagonalsMinMax(int[][] matrix) {
        int n = matrix.length;
        int min1 = Integer.MAX_VALUE, max1 = Integer.MIN_VALUE; 
        int min2 = Integer.MAX_VALUE, max2 = Integer.MIN_VALUE; 
        
        for (int i = 0; i < n; i++) {
        
            min1 = Math.min(min1, matrix[i][i]);
            max1 = Math.max(max1, matrix[i][i]);
            min2 = Math.min(min2, matrix[i][n - i - 1]);
            max2 = Math.max(max2, matrix[i][n - i - 1]);
        }
        System.out.println("Smallest Element - 1: " + min1);
        System.out.println("Greatest Element - 1: " + max1);
        System.out.println("Smallest Element - 2: " + min2);
        System.out.println("Greatest Element - 2: " + max2);
    }

    public static void main(String[] args) {
        int n = 5; 
        int[][] matrix = {
            {7, 8, 9, 0, 1},
            {2, 3, 4, 5, 6},
            {5, 4, 2, 0, 8},
            {23, 5, 6, 8, 9},
            {12, 5, 6, 7, 32}
        };
        
        Main obj = new Main();
        obj.diagonalsMinMax(matrix);
    }
}
