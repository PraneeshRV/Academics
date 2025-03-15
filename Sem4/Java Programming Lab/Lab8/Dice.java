import java.util.*;

public class Dice {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        HashSet<Integer> uniqueValues = new HashSet<>();

        int n = Integer.parseInt(scanner.nextLine()); // Number of dice rolls

        for (int i = 0; i < n; i++) {
            int diceRoll = Integer.parseInt(scanner.nextLine());
            uniqueValues.add(diceRoll); // Add only unique values
        }

        System.out.println("Unique Dice Values: " + uniqueValues);
        scanner.close();
    }
}