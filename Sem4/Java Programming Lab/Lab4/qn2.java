import java.util.Scanner;
class Employee {
    protected int empId;
    protected float salary;
    
    Employee(int id, float sal) {
        empId = id;
        salary = sal;
    }
}
class EmpLevel extends Employee {
    private int level;
    
    EmpLevel(int id, float sal) {
        super(id, sal);
        if(salary > 100)
            level = 1;
        else
            level = 2;
    }
    
    void display() {
        System.out.println(empId);
        System.out.println(salary);
        System.out.println(level);
    }
}
public class qn2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter employee ID:");
        int id = sc.nextInt();
        System.out.println("Enter salary:");
        float salary = sc.nextFloat();
        
        EmpLevel emp = new EmpLevel(id, salary);
        emp.display();
        
        sc.close();
    }
}