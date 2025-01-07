
class Person {
    private String name;
    
    public Person(String name) {
        this.name = name;
    }
    
    public String getName() {
        return name;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public void displayName() {
        System.out.print("Name : " + name);
    }
}

class Staff extends Person {
    private int staffId;
    
    public Staff(String name, int staffId) {
        super(name);
        this.staffId = staffId;
    }
    
    public int getStaffId() {
        return staffId;
    }
    
    public void setStaffId(int staffId) {
        this.staffId = staffId;
    }
    
    public void displayStaffId() {
        System.out.print("\nStaff Id : " + staffId);
    }
}

class TemporaryStaff extends Staff {
    private int days;
    private int hoursworked;
    private static final int RATE_PER_HOUR = 50;
    
    public TemporaryStaff(String name, int staffId, int days, int hoursworked) {
        super(name, staffId);
        this.days = days;
        this.hoursworked = hoursworked;
    }
    
    public int getDays() {
        return days;
    }
    
    public void setDays(int days) {
        this.days = days;
    }
    
    public int getHoursworked() {
        return hoursworked;
    }
    
    public void setHoursworked(int hoursworked) {
        this.hoursworked = hoursworked;
    }
    
    public int calculateSalary() {
        return days * hoursworked * RATE_PER_HOUR;
    }
    
    public void displayDetails() {
        displayName();
        displayStaffId();
        System.out.println("\nNo. of Days : " + days);
        System.out.println("No. of Hours Worked : " + hoursworked);
        System.out.println("Total Salary : " + calculateSalary());
    }
}

class qn5 {
    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        
        String name = scanner.nextLine();
        int staffId = scanner.nextInt();
        int days = scanner.nextInt();
        int hours = scanner.nextInt();
        
        TemporaryStaff staff = new TemporaryStaff(name, staffId, days, hours);
        staff.displayDetails();
        
        scanner.close();
    }
}
