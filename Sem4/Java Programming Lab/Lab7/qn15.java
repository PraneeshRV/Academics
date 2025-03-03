import java.util.*;
public class qn15 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < input.length(); i++) {
            if (Character.isDigit(input.charAt(i))) {
                int count = Character.getNumericValue(input.charAt(i));
                char character = input.charAt(i + 1);
                for (int j = 0; j < count; j++) {
                    result.append(character);
                }
                i++;
            }
        }
        System.out.println(result.toString());
    }
}