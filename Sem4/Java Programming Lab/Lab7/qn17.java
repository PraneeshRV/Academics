import java.util.Scanner;
public class qn17 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        String result = input.replaceAll(" ", "");
        System.out.println(result);
    }
}