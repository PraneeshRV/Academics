public class Qn3 {
    public static void main(String[] args) {
        System.out.print("Enter a number: ");
        java.util.Scanner sc = new java.util.Scanner(System.in);
        int num = sc.nextInt();
        int sum = 0;
        
        for(int i = 1; i < num; i++) {
            if(num % i == 0) {
                sum += i;
            }
        }
        
        if(sum == num) {
            System.out.println(num + " Perfect number");
        } else {
            System.out.println(num + " Not perfect number");
        }
        
        sc.close();
    }
}
