import java.util.*;

public class Mail {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int N = scanner.nextInt();
        scanner.nextLine(); 

        List<String> emailList = new ArrayList<>();

        for (int i = 0; i < N; i++) {
            String email = scanner.nextLine().trim();
            if (!emailList.contains(email)) {
                emailList.add(email);
            }
        }

        String csvEmails = scanner.nextLine().trim();
        String[] emailsToSearch = csvEmails.split(",");
        List<String> searchList = Arrays.asList(emailsToSearch);

        if (emailList.containsAll(searchList)) {
            System.out.println("Email addresses are present");
        } else {
            System.out.println("Email addresses are not present");
        }

        scanner.close();
    }
}
