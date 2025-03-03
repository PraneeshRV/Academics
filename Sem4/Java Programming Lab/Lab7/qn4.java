import java.util.Scanner;
public class qn4 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        scanner.nextLine();
        String[] actions = scanner.nextLine().split(" ");
        boolean followedInstructions = true;
        for (int i = 0; i < N - 1; i++) {
            if (actions[i].equals("cookie") && !actions[i + 1].equals("juice")) {
                followedInstructions = false;
                break;
            }
        }
        if (actions[N - 1].equals("cookie")) {
            followedInstructions = false;
        }

        if (followedInstructions) {
            System.out.println("Yes");
        } else {
            System.out.println("No");
        }
        scanner.close();
    }
}