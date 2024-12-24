import java.util.Scanner;
public class Qn5 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a number: ");
        int num = sc.nextInt();
        int reverse = 0;
        
        System.out.println("Given Digits :" + num);
        
        while(num != 0) {
            int digit = num % 10;
            reverse = reverse * 10 + digit;
            num = num / 10;
        }
        
        System.out.println("Reverse Digits :" + reverse);
        sc.close();
    }
}
