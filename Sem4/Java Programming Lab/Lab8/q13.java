import java.util.*;

public class q13 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<List<Integer>> remainingTickets = new ArrayList<>();

        // Read booked ticket counts for 5 days
        for (int i = 0; i < 5; i++) {
            String[] input = scanner.nextLine().split(",");
            List<Integer> dayList = new ArrayList<>();
            for (String s : input) {
                int booked = Integer.parseInt(s);
                dayList.add(100 - booked);  // Calculate remaining tickets
            }
            remainingTickets.add(dayList);
        }

        // Read the day number for query
        int day = scanner.nextInt();

        // Print remaining tickets for the requested day
        System.out.println("Remaining tickets:" + remainingTickets.get(day - 1));

        scanner.close();
    }
}
