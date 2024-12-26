
import java.util.Scanner;

class Time{
private int hour, minute, second;

public Time(int h, int m, int s) {
    this.hour = h;
    this.second = s;
    this.minute = m;
}

public Time add(Time other){
    int new_second = this.second + other.second;
    int new_minute = this.minute + other.minute + new_second/60;
    int new_hour = this.hour +other.hour + new_minute/60;

    return new Time(new_hour, new_minute%60, new_second%60);
}

public void display(){
    System.out.print(hour+" hours");
    System.out.print(" "+ minute+" minutes");
    System.out.print(" " +second+" seconds");
}
}

public class Q2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("enter the first time");
        Time time1 = new Time(scanner.nextInt(), scanner.nextInt(), scanner.nextInt());

        System.out.println("Enter the second time");
        Time time2 = new Time(scanner.nextInt(), scanner.nextInt(), scanner.nextInt());

        System.out.println("final Time is :");
        Time result = time1.add(time2);
        
        result.display();
    }
}
