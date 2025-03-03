import java.util.*;
public class qn11 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String s = scanner.nextLine();
        scanner.close();
        int countA = 0;
        int countB = 0;
        for (char ch : s.toCharArray()) {
            if (ch == 'a') {
                countA++;
            } else if (ch == 'b') {
                countB++;
            }
        }
        int result = Math.min(countA, countB);
        System.out.println(result);
    }
}