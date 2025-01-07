import java.util.Scanner;
class Bicycle {
    protected int gears;
    protected int speed;
    
    public Bicycle(int gears, int speed) {
        this.gears = gears;
        this.speed = speed;
    }
    
    public String toString() {
        return "No of gears are " + gears + " speed of bicycle is " + speed;
    }
}
class MontaneBike extends Bicycle {
    private int seatHeight;
    
    public MontaneBike(int gears, int speed, int seatHeight) {
        super(gears, speed);
        this.seatHeight = seatHeight;
    }
    
    public String toString() {
        return super.toString() + " seat height is " + seatHeight;
    }
}
public class qn4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int gears = sc.nextInt();
        int speed = sc.nextInt();
        int seatHeight = sc.nextInt();
        
        MontaneBike mb = new MontaneBike(gears, speed, seatHeight);
        System.out.println(mb.toString());
        
        sc.close();
    }
}