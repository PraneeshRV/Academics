
import java.util.Scanner;

public class Qn7 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a number: ");
        int num = sc.nextInt();
        

        String binary = Integer.toBinaryString(num);
        System.out.println("Binary representation: " + binary);
        
        int maxZeros = 0;
        int currentZeros = 0;
 
        for (int i = 0; i < binary.length(); i++) {
            if (binary.charAt(i) == '0') {
                currentZeros++;
                maxZeros = Math.max(maxZeros, currentZeros);
            } else {
                currentZeros = 0;
            }
        }
        
        System.out.println("Longest sequence of zeros: " + maxZeros);
        sc.close();
    }
}
