import java.util.Scanner;
public class qn16 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String str = scanner.nextLine();
        int rotations = scanner.nextInt();
        int length = str.length();
        rotations = rotations % length;
        String rotatedString = str.substring(rotations) +
                str.substring(0, rotations);
        System.out.println(rotatedString);
    }
}