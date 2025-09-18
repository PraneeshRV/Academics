import java.util.Scanner;
class Account extends Thread {
    private String accountNumber;
    private double balance;
    private String accountHoldername;
    public Account() {
        accountNumber = "";
        balance = 0.0;
        accountHoldername = "";
    }
    public Account(String accountNumber, double balance, String accountHoldername) {
        this.accountNumber = accountNumber;
        this.balance = balance;
        this.accountHoldername = accountHoldername;
    }
    public String getAccountNumber() {
        return accountNumber;
    }   
    public void setAccountNumber(String accountNumber) {
        this.accountNumber = accountNumber;
    }   
    public double getBalance() {
        return balance;
    }   
    public void setBalance(double balance) {
        this.balance = balance;
    }   
    public String getAccountHoldername() {
        return accountHoldername;
    }   
    public void setAccountHoldername(String accountHoldername) {
        this.accountHoldername = accountHoldername;
    }  
    @Override
    public void run() {
        double interest;
        if(balance >= 10000) {
            interest = balance * 0.08;
        } else {
            interest = balance * 0.05;
        }
        System.out.printf("%.2f\n", interest);
        System.out.printf("%.2f\n", balance + interest);
    }
}
public class qn1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        Account[] accounts = new Account[n];
        
        for(int i = 0; i < n; i++) {
            String accNum = sc.next();
            double bal = sc.nextDouble();
            String name = sc.next();
            accounts[i] = new Account(accNum, bal, name);
            accounts[i].start();
        }
        
        sc.close();
    }
}
