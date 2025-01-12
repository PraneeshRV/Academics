import java.util.Scanner;
class qn9 {
    public void Quantity(int r, int h) {
        double volume = (1.0/3.0) * Math.PI * r * r * h;
        System.out.printf("Volume of cone: %.2f\n", volume);
    }
    
    public void Quantity(int r) {
        double volume = (4.0/3.0) * Math.PI * r * r * r;
        System.out.printf("Volume of ball: %.2f\n", volume);
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        qn9 ic = new qn9();
        
        System.out.println("Enter radius and height for cone (separated by space):");
        int r1 = sc.nextInt();
        int h = sc.nextInt();
        ic.Quantity(r1, h);
        
        System.out.println("\nEnter radius for ball:");
        int r2 = sc.nextInt();
        ic.Quantity(r2);
        
        sc.close();
    }
}
