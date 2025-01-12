import java.util.Scanner;
class qn6 {
    public void fun1(int a, int b) {
        System.out.println("Sum = " + (a + b));
    }

    public void fun1(int a, int b, int c) {
        System.out.println("Product = " + (a * b * c));
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        qn6 obj = new qn6();

        System.out.println("Enter the number of elements:");
        int n = sc.nextInt();

        if (n <= 0 || n > 3) {
            System.out.println("WRONG INPUT");
            sc.close();
            return;
        }

        System.out.println("Enter the elements separated by space:");
        if (n == 2) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            obj.fun1(a, b);
        } else if (n == 3) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int c = sc.nextInt();
            obj.fun1(a, b, c);
        }
        sc.close();
    }}
