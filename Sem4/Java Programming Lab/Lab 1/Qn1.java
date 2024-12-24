import java.util.Scanner;
public class Qn1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in); 
        System.out.print("Enter two integers (second should be greater than first): ");
        int start = scanner.nextInt();
        int end = scanner.nextInt();
        
        if (start >= end) {
            System.out.println("The second integer must be greater than the first.");
            
        }
        System.out.println("Prime numbers between " + start + " and " + end + ":");
        for (int i = start; i <= end; i++) {
            if (isPrime(i)) {
                System.out.print(i + " ");
            }
        }
        scanner.close();
    }
    public static boolean isPrime(int number) {
        if (number <= 1) {
            return false;
        }
        for (int i = 2; i <= Math.sqrt(number); i++) {
            if (number % i == 0) {
                return false;
            }
        }
        return true;
    } 
}