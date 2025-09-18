class Student {
    private int id;
    private String name;
    public Student(int id, String name) {
        this.id = id;
        this.name = name;
    }
    public Student(Student other) {
        this.id = other.id;
        this.name = other.name;
    }
    public void display() {
        System.out.println(id + " " + name);
    }
}
public class qn2 {
    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        
        System.out.println("Enter ID and name");
        int id = scanner.nextInt();
        String name = scanner.next();
        Student student1 = new Student(id, name);
        Student student2 = new Student(student1);
        System.out.println("Details stored in object 1");
        student1.display();
        System.out.println("Details stored in object 2 after copied from object 1");
        student2.display(); 
        scanner.close();
    }
}
