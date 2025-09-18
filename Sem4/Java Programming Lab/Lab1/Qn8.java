import java.util.Scanner;
public class Qn8{
    public static void main(String[] args) {
        System.out.print("Enter teh Number: ");
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        double sum = 0;
        for(int i = 1; i <= n; i++) {
            sum += i/factorial(i);
        }
        System.out.println(sum);
        sc.close();
    } 
    public static double factorial(int n) {
        double fact = 1;
        for(int i = 1; i <= n; i++) {
            fact *= i;
        }
        return fact;
    }
}