import java.util.*;

class Passenger {
    String name;
    int age;

    public Passenger(String name, int age) {
        this.name = name;
        this.age = age;
    }
}

class SortByAgeDescending implements Comparator<Passenger> {
    public int compare(Passenger p1, Passenger p2) {
        return Integer.compare(p2.age, p1.age); // Sort in descending order
    }
}

public class AgeSort {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter number of passengers:");
        int n = Integer.parseInt(scanner.nextLine()); // Read number of passengers
        List<Passenger> passengers = new ArrayList<>();
        
        for (int i = 0; i < n; i++) {
            System.out.print("Enter name: ");

            String name = scanner.nextLine();
            System.out.print("Enter age: ");

            int age = Integer.parseInt(scanner.nextLine());
            passengers.add(new Passenger(name, age));
        }
        
        passengers.sort(new SortByAgeDescending());
        
        System.out.println("Passengers Details by age(High to Low)");
        int index = 1;
        for (Passenger p : passengers) {
            System.out.println(index + " " + p.name + " " + p.age);
            index++;
        }
        
        scanner.close();
    }
}
