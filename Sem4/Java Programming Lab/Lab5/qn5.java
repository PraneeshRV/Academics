import java.util.Scanner;
abstract class Move {
    abstract int minFrontMoves(int[] arr);
}
public class qn5 extends Move {
    @Override
    int minFrontMoves(int[] arr) {
        int n = arr.length;
        int[] sortedArr = arr.clone();
        java.util.Arrays.sort(sortedArr);
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i] != sortedArr[i]) {
                count++;
                int temp = arr[i];
                for (int j = i; j > 0; j--) {
                    arr[j] = arr[j - 1];
                }
                arr[0] = temp;
            }
        }
        return count;
    }
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter the number of elements in the array:");
            int n = scanner.nextInt();
            int[] arr = new int[n];
            System.out.println("Enter the elements of the array:");
            for (int i = 0; i < n; i++) {
                arr[i] = scanner.nextInt();
            }
            qn5 main = new qn5();
            int result = main.minFrontMoves(arr);
            System.out.println("Minimum number of front moves required to sort the array:");
            System.out.println(result);
            scanner.close();
        }}