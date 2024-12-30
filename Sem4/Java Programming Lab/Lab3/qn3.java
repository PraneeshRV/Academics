import java.util.Scanner;
class ItemType {
    private String name;
    private double deposit;
    private double costPerDay;
    public ItemType() { }
    public ItemType(String name, double deposit, double costPerDay) {
        this.name = name;
        this.deposit = deposit;
        this.costPerDay = costPerDay;
    } 
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public double getDeposit() {
        return deposit;
    }
    public void setDeposit(double deposit) {
        this.deposit = deposit;
    }
    public double getCostPerDay() {
        return costPerDay;
    }
    public void setCostPerDay(double costPerDay) {
        this.costPerDay = costPerDay;
    }
}
class ItemTypeBO {
    public void searchDetail(String search, ItemType[] item, int n) {
        boolean found = false;
        for(int i = 0; i < n; i++) {
            if(item[i].getName().equals(search)) {
                System.out.printf("%s %.1f %.1f\n", item[i].getName(), item[i].getDeposit(), item[i].getCostPerDay());
                found = true;
                break;
            }
        }
        if(!found) {
            System.out.println("Searched item Type not found");
        }
    }
    
    public void display(ItemType[] item, int n) {
        for(int i = 0; i < n; i++) {
            System.out.printf("%s %.1f %.1f\n", item[i].getName(), item[i].getDeposit(), item[i].getCostPerDay());
        }
    }
}

public class qn3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ItemType[] items = new ItemType[10];
        
        int n = sc.nextInt();
        for(int i = 0; i < n; i++) {
            String name = sc.next();
            double deposit = sc.nextDouble();
            double costPerDay = sc.nextDouble();
            items[i] = new ItemType(name, deposit, costPerDay);
        }
        
        String search = sc.next();
        ItemTypeBO bo = new ItemTypeBO();
        bo.searchDetail(search, items, n);
        bo.display(items, n);
        
        sc.close();
    }
}
