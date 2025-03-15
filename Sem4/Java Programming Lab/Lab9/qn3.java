import java.util.*;
import java.text.DecimalFormat;

class ItemType extends Thread {
    private String name1;
    private double deposit;
    private double costPerItem;
    private int noOfItems;
    
    public ItemType() {
        this.name1 = "";
        this.deposit = 0.0;
        this.costPerItem = 0.0;
        this.noOfItems = 0;
    }
    public ItemType(String name1, double deposit, double costPerItem, int noOfItems) {
        this.name1 = name1;
        this.deposit = deposit;
        this.costPerItem = costPerItem;
        this.noOfItems = noOfItems;
    }
    public String getName1() {
        return name1;
    }
    public void setName1(String name1) {
        this.name1 = name1;
    }
    public double getDeposit() {
        return deposit;
    }
    public void setDeposit(double deposit) {
        this.deposit = deposit;
    }
    public double getCostPerItem() {
        return costPerItem;
    }
    public void setCostPerItem(double costPerItem) {
        this.costPerItem = costPerItem;
    }
    public int getNoOfItems() {
        return noOfItems;
    }
    public void setNoOfItems(int noOfItems) {
        this.noOfItems = noOfItems;
    }
    
    @Override
    public void run() {
        DecimalFormat df = new DecimalFormat("#.00");
        double totalAmount = costPerItem * noOfItems;
        System.out.println(df.format(totalAmount));
    }
}

public class qn3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        ItemType[] items = new ItemType[n];
        
        for(int i = 0; i < n; i++) {
            String name = sc.next();
            double deposit = sc.nextDouble();
            double costPerItem = sc.nextDouble();
            int noOfItems = sc.nextInt();
            items[i] = new ItemType(name, deposit, costPerItem, noOfItems);
        }
        
        for(ItemType item : items) {
            item.start();
        }
        
        sc.close();
    }
}
