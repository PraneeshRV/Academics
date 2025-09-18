import java.util.Scanner;
public class qn5 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the event name:");
        String input = scanner.nextLine();
        scanner.close();
        String camelCaseOutput = toCamelCase(input);
        System.out.println(camelCaseOutput);
    }
    public static String toCamelCase(String input) {
        String[] words = input.split(" ");
        StringBuilder camelCaseString = new StringBuilder();

        for (String word : words) {
            if (word.length() > 0) {
                camelCaseString.append(Character.toUpperCase(word.charAt(0)));
                camelCaseString.append(word.substring(1).toLowerCase());
            }
        }
        return camelCaseString.toString();
    }
}