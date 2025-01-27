import java.util.Scanner;
interface Product {
    void ProductDetails();
    void show_Bill();
}
class Customer {
    String id, name;
    public void getdetails() {
        Scanner sc = new Scanner(System.in);
        id = sc.nextLine();
        name = sc.nextLine();
    }
    public void showdetails() {
        System.out.println("ID:" + id);
        System.out.println("NAME:" + name);
    }
}
class OrderOnline extends Customer implements Product {
    int numItems;
    String[] productNames;
    double[] productCosts;
    double totalBill = 0;
    @Override
    public void ProductDetails() {
        Scanner sc = new Scanner(System.in);
        numItems = sc.nextInt();
        productNames = new String[numItems];
        productCosts = new double[numItems];
        for (int i = 0; i < numItems; i++) {
            productNames[i] = sc.next();
            productCosts[i] = sc.nextDouble();
            totalBill += productCosts[i];
        }
        if (totalBill <= 10000) {
        } else if (totalBill > 10000 && totalBill <= 30000) {
            totalBill += totalBill * 0.05;
        } else if (totalBill > 30000 && totalBill <= 50000) {
            totalBill += totalBill * 0.07;
        } else {
            totalBill += totalBill * 0.09;
        }
    }
    @Override
    public void show_Bill() {
        System.out.println("Bill:" + totalBill);
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(); 
        for (int i = 0; i < n; i++) {
            OrderOnline customer = new OrderOnline();
            customer.getdetails();
            customer.ProductDetails();
            customer.showdetails();
            customer.show_Bill();
        }
    }
}
