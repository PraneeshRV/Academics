import java.util.*;
public class qn10 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String S = scanner.nextLine().trim();
        scanner.close();
        if (isSloganValid(S)) {
            System.out.println("Yes");
        } else {
            System.out.println("No");
        }
    }

    public static boolean isSloganValid(String S) {
        int[] frequency = new int[26];
        for (char c : S.toCharArray()) {
            frequency[c - 'a']++;
        }
        int totalLength = S.length();
        for (int i = 0; i < 26; i++) {
            int count = frequency[i];
            if (count > 0 && count == totalLength - count) {
                return true;
            }
        }
        return false;
    }
}