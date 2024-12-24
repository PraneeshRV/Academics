
public class Qn1 {
    private double weight;
    private double height;
    private double bmi;
    private String grade;

    public Qn1(double weight, double height) {
        this.weight = weight;
        this.height = height;
        this.bmi = calculateBMI();
        this.grade = calculateGrade();
    }

    private double calculateBMI() {
        return weight / (height * height);
    }

    private String calculateGrade() {
        if (bmi < 18.5) {
            return "U";
        } else if (bmi >= 18.5 && bmi < 25.0) {
            return "N";
        } else if (bmi >= 25.0 && bmi < 30.0) {
            return "H";
        } else {
            return "O";
        }
    }

    public void displayBMI() {
        System.out.println(grade);
    }

    public static void main(String[] args) {
        System.out.print("Underweight: U, Normal: N, Overweight: H, Obese: O\n");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        System.out.print("Enter weight in kg: ");
        double weight = scanner.nextDouble();
        System.out.print("Enter height in meters: ");
        double height = scanner.nextDouble();
        
        Qn1 calculator = new Qn1(weight, height);
        calculator.displayBMI();
        
        scanner.close();
    }
}
