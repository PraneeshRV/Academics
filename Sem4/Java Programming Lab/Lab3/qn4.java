import java.util.Scanner;
class StallCategory {
    public String name;
    public String detail;
    
    public StallCategory() {
        name = "";
        detail = "";
    }
    public StallCategory(String name, String detail) {
        this.name = name;
        this.detail = detail;
    }
    public StallCategory(StallCategory object) {
        this.name = object.name;
        this.detail = object.detail;
    }
    public String getName() {
        return name;
    } 
    public String getDetail() {
        return detail;
    }
    public void setName(String name) {
        this.name = name;
    }
    public void setDetail(String detail) {
        this.detail = detail;
    }
}

public class qn4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String name = sc.nextLine();
        String detail = sc.nextLine();

        StallCategory stall1 = new StallCategory(name, detail);

        StallCategory stall2 = new StallCategory(stall1);

        System.out.println("Using Parameterized Constructor:");
        System.out.println("Name:" + stall1.getName());
        System.out.println("Detail:" + stall1.getDetail());
        
        System.out.println("\nUsing Copy Constructor:");
        System.out.println("Name:" + stall2.getName());
        System.out.println("Detail:" + stall2.getDetail());
        
        sc.close();
    }
}
