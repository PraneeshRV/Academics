import java.util.*;

public class q12 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        TreeMap<Integer, Integer> ticketSales = new TreeMap<>();

        int n = Integer.parseInt(scanner.nextLine()); // Read number of events

        for (int i = 0; i < n; i++) {
            int price = scanner.nextInt();
            int seats = scanner.nextInt();
            ticketSales.put(price, seats); // Automatically sorts by price
        }

        System.out.println(ticketSales);
        scanner.close();
    }
}
