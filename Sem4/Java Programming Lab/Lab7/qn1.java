import java.util.Scanner;

public class qn1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a string:");
        String input = scanner.nextLine();
        scanner.close();

        String result = removeConsecutiveVowels(input);
        System.out.println("Output: " + result);
    }

    private static String removeConsecutiveVowels(String str) {
        StringBuilder sb = new StringBuilder();
        char[] vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        boolean lastWasVowel = false;

        for (char c : str.toCharArray()) {
            boolean isVowel = false;
            for (char v : vowels) {
                if (c == v) {
                    isVowel = true;
                    break;
                }
            }

            if (!(lastWasVowel && isVowel)) {
                sb.append(c);
            }
            lastWasVowel = isVowel;
        }

        return sb.toString();
    }
}