import java.util.Scanner;
class PoolTable {
    public double length;
    public double width;
    public double pocketSize;

    public double calculatePerimeter() {
        return 2 * (length + width);
    }

    public double calculatePocketPerimeter() {
        return Math.PI * pocketSize;
    }
}

public class qn7 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        PoolTable pool = new PoolTable();

        System.out.println("Enter the length of the pool table in meters:");
        pool.length = sc.nextDouble();

        System.out.println("Enter the width of the pool table in meters:");
        pool.width = sc.nextDouble();

        System.out.println("Enter the diameter of the pocket in meters:");
        pool.pocketSize = sc.nextDouble();

        System.out.println("Perimeter of pool table:");
        System.out.printf("%.1f\n", pool.calculatePerimeter());

        System.out.println("Perimeter of pocket:");
        System.out.printf("%.1f\n", pool.calculatePocketPerimeter());

        sc.close();
    }
}
