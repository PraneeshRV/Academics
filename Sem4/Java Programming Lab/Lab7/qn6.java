import java.util.Scanner;

public class qn6 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String emailAddress = scanner.nextLine();
        scanner.close();
        if (isValidEmail(emailAddress)) {
            System.out.println("Valid email address");
        } else {
            System.out.println("Invalid email address");
        }
    }

    public static boolean isValidEmail(String email) {
        String[] validDomains = { "com", "in", "net", "org" };
        int atIndex = email.indexOf('@');
        if (atIndex == -1) {
            return false;
        }
        String domainPart = email.substring(atIndex + 1);
        for (String domain : validDomains) {
            if (domainPart.endsWith(domain)) {
                return true;
            }
        }
        return false;
    }
}