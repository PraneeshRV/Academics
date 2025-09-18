
import java.util.Scanner;

abstract class AbstractClass {
    abstract int getValue();
    abstract int divisorSum(int n);
}

class Calculator extends AbstractClass {
    int getValue() {
        try (Scanner sc = new Scanner(System.in)) {
            return sc.nextInt();
        }
    }
    
    int divisorSum(int n) {
        int sum = 0;
        for(int i = 1; i <= n; i++) {
            if(n % i == 0) {
                sum += i;
            }
        }
        return sum;
    }
}
class qn2 {
    public static void main(String[] args) {
        Calculator calc = new Calculator();
        System.out.print("Enter a number: ");
        int n = calc.getValue();
        System.out.println("Sum of divisors: " + calc.divisorSum(n));
    }
}
