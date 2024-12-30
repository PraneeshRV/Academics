import java.util.Scanner;
class Wall {
    private double length;
    private double height;   
    Wall(double length, double height) {
        this.length = length;
        this.height = height;
    }
    public double calculateArea() {
        return length * height;
    }
}public class qn1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter length of wall 1");
        double length1 = sc.nextDouble();
        System.out.println("Enter height of wall 1");
        double height1 = sc.nextDouble();
        Wall wall1 = new Wall(length1, height1);
        System.out.println("Enter length of wall 2");
        double length2 = sc.nextDouble();
        System.out.println("Enter height of wall 2");
        double height2 = sc.nextDouble();
        Wall wall2 = new Wall(length2, height2);
        
        System.out.printf("Area of Wall 1: %.2f\n", wall1.calculateArea());
        System.out.printf("Area of Wall 2: %.2f\n", wall2.calculateArea());
        
        sc.close();
    }
}
