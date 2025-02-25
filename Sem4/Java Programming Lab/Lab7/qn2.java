import java.util.Scanner;

public class qn2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a string:");
        String input = scanner.nextLine();
        scanner.close();
        
        String result = addAsterisks(input);
        System.out.println("Output: " + result);
    }

    public static String addAsterisks(String str) {
        if (str == null || str.length() <= 1) {
            return str;
        }

        StringBuilder sb = new StringBuilder();
        sb.append(str.charAt(0));

        for (int i = 1; i < str.length(); i++) {
            if (str.charAt(i) == str.charAt(i - 1)) {
                sb.append('*');
            }
            sb.append(str.charAt(i));
        }

        return sb.toString();
    }
}