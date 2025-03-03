import java.util.Scanner;
public class qn9 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String sentence = scanner.nextLine().trim();
        String gibberishText = scanner.nextLine().trim();
        scanner.close();
        if (sentence.contains(gibberishText)) {
            System.out.println("String is found in the sentence");
        } else {
            System.out.println("String is not found in the sentence");
        }
    }
}