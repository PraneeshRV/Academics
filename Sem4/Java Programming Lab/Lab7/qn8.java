import java.util.Scanner;
public class qn8 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String username = scanner.nextLine();
        String uppercaseUsername = username.toUpperCase();
        System.out.println(uppercaseUsername);
        scanner.close();
    }
}