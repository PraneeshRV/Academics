import java.util.Scanner;

public class qn3 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String ticketCode = scanner.nextLine();
        scanner.close();

        if (isAlternating(ticketCode)) {
            System.out.println("Yes");
        } else {
            System.out.println("No");
        }
    }

    private static boolean isAlternating(String code) {
        if (code.length() < 2) {
            return false;
        }

        char first = code.charAt(0);
        char second = code.charAt(1);

        if (first == second) {
            return false;
        }

        for (int i = 0; i < code.length(); i++) {
            if (i % 2 == 0 && code.charAt(i) != first) {
                return false;
            }
            if (i % 2 == 1 && code.charAt(i) != second) {
                return false;
            }
        }

        return true;
    }
}