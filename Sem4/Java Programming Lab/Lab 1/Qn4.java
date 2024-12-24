public class Qn4 {
    public static void pattern(String s) {
        int n = s.length();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j == i || j == n-1-i) {
                    System.out.print(s.charAt(j) + " ");
                } else {
                    System.out.print("  ");
                }
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        System.out.print("Enter a string: ");
        java.util.Scanner sc = new java.util.Scanner(System.in);
        String s = sc.nextLine();
        if (s.length() % 2 == 0) {
            System.out.println("Please enter a string with odd length");
        }
        pattern(s);
        sc.close();
    }   
}