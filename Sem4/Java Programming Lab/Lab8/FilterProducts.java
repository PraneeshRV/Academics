import java.util.*;

public class FilterProducts {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        int N = s.nextInt();
        s.nextLine();

        List<String> productNames = new ArrayList<>();
        List<Integer> productPrices = new ArrayList<>();

        for (int i = 0; i < N; i++) {
            productNames.add(s.nextLine().trim());
            productPrices.add(s.nextInt());
            s.nextLine();
        }

        int X = s.nextInt();

        List<String> filteredProducts = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            if (productPrices.get(i) <= X) {
                filteredProducts.add(productNames.get(i));
            }
        }

        Collections.sort(filteredProducts);

        if (filteredProducts.isEmpty()) {
            System.out.println("No result found");
        } else {
            for (String product : filteredProducts) {
                int index = productNames.indexOf(product);
                System.out.println(product + " : " + productPrices.get(index));
            }
        }

        s.close();
    }
}
