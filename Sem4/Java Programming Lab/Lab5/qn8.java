import java.util.Scanner;
class Employee {
    protected String name;
    protected double basicSalary;
    
    public Employee(String name, double basicSalary) {
        this.name = name;
        this.basicSalary = basicSalary;
    }
    
    public double calculateSalary() {
        return basicSalary;
    }
}

class Manager extends Employee {
    private double bonus;
    
    public Manager(String name, double basicSalary, double bonus) {
        super(name, basicSalary);
        this.bonus = bonus;
    }
    
    @Override
    public double calculateSalary() {
        return basicSalary + bonus;
    }
}

class Engineer extends Employee {
    private double overtimePay;
    
    public Engineer(String name, double basicSalary, double overtimePay) {
        super(name, basicSalary);
        this.overtimePay = overtimePay;
    }
    
    @Override
    public double calculateSalary() {
        return basicSalary + overtimePay;
    }
}

public class qn8 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter Manager Details:");
        System.out.print("Enter Manager name: ");
        String managerName = scanner.nextLine();
        
        System.out.print("Enter Manager basic salary: ");
        double managerBasicSalary = scanner.nextDouble();
        
        System.out.print("Enter Manager bonus: ");
        double managerBonus = scanner.nextDouble();
        scanner.nextLine();
        
        System.out.println("\nEnter Engineer Details:");
        System.out.print("Enter Engineer name: ");
        String engineerName = scanner.nextLine();
        
        System.out.print("Enter Engineer basic salary: ");
        double engineerBasicSalary = scanner.nextDouble();
        
        System.out.print("Enter Engineer overtime pay: ");
        double engineerOvertimePay = scanner.nextDouble();
        
        Manager manager = new Manager(managerName, managerBasicSalary, managerBonus);
        Engineer engineer = new Engineer(engineerName, engineerBasicSalary, engineerOvertimePay);
        
        System.out.println("\nCalculated Salaries:");
        System.out.printf("Manager Salary: %.1f%n", manager.calculateSalary());
        System.out.printf("Engineer Salary: %.1f%n", engineer.calculateSalary());
        
        scanner.close();
    }
}
