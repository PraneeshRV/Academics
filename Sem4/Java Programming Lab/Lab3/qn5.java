import java.util.Scanner;

class Overloading {
    private String name;
    private String day;
    private int temp;

    public Overloading() {
        this.name = "Argentina";
        this.day = "Yesterday";
        this.temp = 29;
    }

    public Overloading(String name, int temp) {
        this.name = name;
        this.day = "Today";
        this.temp = temp;
    }

    public Overloading(String name, String day, int temp) {
        this.name = name;
        this.day = day;
        this.temp = temp;
    }

    public void displayDetails() {
        System.out.println(name + " " + day + " Temperature: " + temp + "\u00B0");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        try {
            String[] input1 = scanner.nextLine().split(" ");
            if (input1.length != 2) {
                throw new IllegalArgumentException("First input must have exactly 2 values: place name and temperature.");
            }
            String place1 = input1[0];
            int temp1 = Integer.parseInt(input1[1]);

            String[] input2 = scanner.nextLine().split(" ");
            if (input2.length != 3) {
                throw new IllegalArgumentException("Second input must have exactly 3 values: place name, day, and temperature.");
            }
            String place2 = input2[0];
            String day2 = input2[1];
            int temp2 = Integer.parseInt(input2[2]);

            Overloading obj1 = new Overloading();
            Overloading obj2 = new Overloading(place1, temp1);
            Overloading obj3 = new Overloading(place2, day2, temp2);

            obj1.displayDetails();
            obj2.displayDetails();
            obj3.displayDetails();
        } catch (NumberFormatException e) {
            System.out.println("Error: Temperature must be an integer.");
        } catch (IllegalArgumentException e) {
            System.out.println("Error: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }
}
