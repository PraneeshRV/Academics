import java.util.*;
public class qn12 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String D = scanner.nextLine();
        if (canMakeUniform(D)) {
            System.out.println("Yes");
        } else {
            System.out.println("No");
        }
        scanner.close();
    }
    public static boolean canMakeUniform(String D) {
        int countZero = 0;
        int countOne = 0;
        for (char c : D.toCharArray()) {
            if (c == '0') {
                countZero++;
            } else if (c == '1') {
                countOne++;
            }
        }
        return countZero == 1 || countOne == 1;
    }
}