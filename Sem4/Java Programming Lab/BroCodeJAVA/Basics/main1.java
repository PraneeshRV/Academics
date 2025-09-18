import java.util.Scanner;
public class main1{

    public static void main(String[] args){
        System.out.print("Enter your Name: ");
        Scanner scanner = new Scanner(System.in);
        String name = scanner.nextLine();
        System.out.print("Hello "+name);
        scanner.close();
    }
}