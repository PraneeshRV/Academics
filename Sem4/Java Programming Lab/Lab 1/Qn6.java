import java.util.Scanner;
public class Qn6 {
    public static void main(String[] args) {
        System.out.println("Enter Enter richie's Number, Riya's Number and Number of Turns ");
        Scanner sc = new Scanner(System.in);
        long a = sc.nextLong();
        long b = sc.nextLong();
        int n = sc.nextInt();  
        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) {
                a *= 2;
            } else {
                b *= 2;
            }
        }       
        System.out.println(a + b);
        sc.close();
    }
}
