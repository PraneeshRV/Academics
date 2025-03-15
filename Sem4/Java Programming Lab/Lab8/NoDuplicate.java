import java.util.*;

public class NoDuplicate {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        int N = s.nextInt();
        s.nextLine();

        List<String> usernameList = new ArrayList<>();

        for (int i = 0; i < N; i++) {
            String username = s.nextLine().trim();
            if (!usernameList.contains(username)) {
                usernameList.add(username);
            }
        }

        System.out.println(usernameList.size());

        s.close();
    }
}
