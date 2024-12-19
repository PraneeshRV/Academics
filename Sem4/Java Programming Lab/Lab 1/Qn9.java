
import java.util.Scanner;

public class Qn9 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter initial incentive amount: ");
        int initialAmount = sc.nextInt();
        System.out.print("Enter number of consecutive days: ");
        int days = sc.nextInt();

        int totalIncentive = 0;
        int currentAmount = initialAmount;
        
        for(int i = 1; i <= days; i++) {
            totalIncentive += currentAmount;
            currentAmount += 200;
        }
        
        System.out.println("Total Punctuality Incentive: " + totalIncentive);
        
        sc.close();
    }
}
