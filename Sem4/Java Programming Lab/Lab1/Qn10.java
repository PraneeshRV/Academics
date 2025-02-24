import java.util.Scanner;
public class Qn10 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the value of s: ");
        int s = scanner.nextInt();
        System.out.print("Enter the value of Number N: ");
        int N = scanner.nextInt();
        
             
        int count = 0;
        System.out.print("Numbers with streak : ");
        for (int n = 2; n < N; n++) {
            if (streak(n) == s) {
                count++;
            }
        }
        
        System.out.println(count);
        
        scanner.close();
    }

    public static int streak(int n) {
        int k = 1;
        while ((n + k) % (k + 1) == 0) {
            k++;
        }
        return k;
    }
}
