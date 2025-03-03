import java.util.*;
public class qn14 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String X = scanner.nextLine();
        String Y = scanner.nextLine();
        if (X.length() != Y.length()) {
            System.out.println("No");
            return;
        }
        for (int i = 0; i < X.length(); i++) {
            char xChar = X.charAt(i);
            char yChar = Y.charAt(i);
            if (xChar != yChar && xChar != '?' && yChar != '?') {
                System.out.println("No");
                return;
            }
        }
        System.out.println("Yes");
    }
}