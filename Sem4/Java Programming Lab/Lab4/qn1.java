import java.util.Scanner;
class Vehicle {
    protected String type;
    
    public Vehicle(String type) {
        this.type = type;
    }
    
    public void displayType() {
        System.out.println("Type: " + type);
    }
}

class Car extends Vehicle {
    private String brand;
    
    public Car(String type, String brand) {
        super(type);
        this.brand = brand;
    }
    
    public void displayBrand() {
        System.out.println("Brand: " + brand);
    }
}

public class qn1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        String type = scanner.nextLine();
        String brand = scanner.nextLine();
        
        Car car = new Car(type, brand);
        car.displayType();
        car.displayBrand();
        
        scanner.close();
    }
}
