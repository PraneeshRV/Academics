import java.util.*;

class Student {
    private int rollNo;
    private String name;
    private String address;
    private int rank;

    public Student(int rollNo, String name, String address, int rank) {
        this.rollNo = rollNo;
        this.name = name;
        this.address = address;
        this.rank = rank;
    }

    public int getRollNo() {
        return rollNo;
    }

    public String getName() {
        return name;
    }

    public String getAddress() {
        return address;
    }

    public int getRank() {
        return rank;
    }

    @Override
    public String toString() {
        return rollNo + " " + name + " " + address + " " + rank;
    }
}

class SortByRollNo implements Comparator<Student> {
    @Override
    public int compare(Student s1, Student s2) {
        return Integer.compare(s1.getRollNo(), s2.getRollNo());
    }
}

class SortByName implements Comparator<Student> {
    @Override
    public int compare(Student s1, Student s2) {
        return s1.getName().compareToIgnoreCase(s2.getName());
    }
}

class SortByRank implements Comparator<Student> {
    private boolean ascending;

    public SortByRank(boolean ascending) {
        this.ascending = ascending;
    }

    @Override
    public int compare(Student s1, Student s2) {
        return ascending ? Integer.compare(s1.getRank(), s2.getRank()) : Integer.compare(s2.getRank(), s1.getRank());
    }
}

public class StudentManagement {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<Student> students = new ArrayList<>();
        
        while (true) {
            System.out.println("Student Interactive Console :");
            System.out.println("1). Add User");
            System.out.println("2). Sort Student List by Roll no");
            System.out.println("3). Sort Student List by Name");
            System.out.println("4). Sort Students by Rank");
            System.out.println("5). Exit from System");
            System.out.print("Enter your choice: ");
            
            int choice = scanner.nextInt();
            scanner.nextLine();
            
            switch (choice) {
                case 1:
                    System.out.print("Enter the rollno, name, address and rank (separated by comma): ");
                    String[] details = scanner.nextLine().split(",");
                    if (details.length != 4) {
                        System.out.println("Invalid Input. Try again !!!");
                        continue;
                    }
                    students.add(new Student(
                        Integer.parseInt(details[0].trim()),
                        details[1].trim(),
                        details[2].trim(),
                        Integer.parseInt(details[3].trim())
                    ));
                    break;
                
                case 2:
                    students.sort(new SortByRollNo());
                    System.out.println("Students List sorted by rollno");
                    students.forEach(System.out::println);
                    break;
                
                case 3:
                    students.sort(new SortByName());
                    System.out.println("Students List sorted by name");
                    students.forEach(System.out::println);
                    break;
                
                case 4:
                    System.out.print("Sort by ascending or descending (asc / des): ");
                    String order = scanner.nextLine().trim().toLowerCase();
                    if (!order.equals("asc") && !order.equals("des")) {
                        System.out.println("Invalid Input. Try again !!!");
                        continue;
                    }
                    students.sort(new SortByRank(order.equals("asc")));
                    System.out.println("Students List sorted by rank");
                    students.forEach(System.out::println);
                    break;
                
                case 5:
                    System.out.println("Exiting ....");
                    scanner.close();
                    return;
                
                default:
                    System.out.println("Invalid Input. Try again !!!");
            }
        }
    }
}
