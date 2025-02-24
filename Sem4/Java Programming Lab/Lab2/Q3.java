import java.util.Scanner;

class Prof {
    int id;
    String name;
    String dept;
    int age;
    double salary;

    
    public Prof(int id, String name, String dept, int age, double salary) {
        this.id = id;
        this.name = name;
        this.dept = dept;
        this.age = age;
        this.salary = salary;
    }
}

public class Q3 {

    
    public static Prof findHighestSalaryProfessor(Prof[] professors) {
        Prof highest = professors[0]; 
        for (Prof prof : professors) {
            if (prof.salary > highest.salary) {
                highest = prof;
            }
        }
        return highest;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
       
        System.out.print("Enter the number of professors: ");
        int n = sc.nextInt();
        sc.nextLine(); 

       
        Prof[] professors = new Prof[n];

        
        for (int i = 0; i < n; i++) {
            System.out.println("Enter details for professor " + (i + 1));

            System.out.print("ID: ");
            int id = sc.nextInt();
            sc.nextLine(); 

            System.out.print("Name: ");
            String name = sc.nextLine();

            System.out.print("Department: ");
            String dept = sc.nextLine();

            System.out.print("Age: ");
            int age = sc.nextInt();

            System.out.print("Salary: ");
            double salary = sc.nextDouble();
            sc.nextLine(); 

            
            professors[i] = new Prof(id, name, dept, age, salary);
        }

        
        Prof highestSalaryProf = findHighestSalaryProfessor(professors);

        sc.close();
        System.out.println("\nProfessor with the highest salary:");
        System.out.println("ID: " + highestSalaryProf.id);
        System.out.println("Name: " + highestSalaryProf.name);
        System.out.println("Salary: " + highestSalaryProf.salary);
    }
}
