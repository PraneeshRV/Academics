import java.util.*;

public class q10 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt(); // Number of products
        scanner.nextLine(); // Consume newline

        Map<String, Integer> products = new HashMap<>();

        for (int i = 0; i < n; i++) {
            String product = scanner.nextLine();   // Product name
            int price = scanner.nextInt();        // Product price
            scanner.nextLine(); // Consume newline
            products.put(product, price);
        }

        int x = scanner.nextInt(); // Price filter
        scanner.close();

        // Filter and sort the products by name
        TreeMap<String, Integer> sortedProducts = new TreeMap<>();
        for (var entry : products.entrySet()) {
            if (entry.getValue() <= x) {
                sortedProducts.put(entry.getKey(), entry.getValue());
            }
        }

        // Print results
        if (sortedProducts.isEmpty()) {
            System.out.println("No result found");
        } else {
            sortedProducts.forEach((key, value) -> System.out.println(key + " : " + value));
        }
    }
}
