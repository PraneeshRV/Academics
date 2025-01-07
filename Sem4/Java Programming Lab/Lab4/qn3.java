import java.util.Scanner;
class Account {
    private int account_number;
    private int account_balance;
    
    public void setAccountNumber(int accno) {
        this.account_number = accno;
    }
    
    public void setAccountBalance(int bal) {
        this.account_balance = bal;
    }
    
    public int getAccountNumber() {
        return account_number;
    }
    
    public int getAccountBalance() {
        return account_balance;
    }
}
class User extends Account {
    private String username;
    
    public void setUsername(String name) {
        this.username = name;
    }
    
    public String getUsername() {
        return username;
    }
}
class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        User[] users = new User[n];
        
        for(int i = 0; i < n; i++) {
            users[i] = new User();
            users[i].setAccountNumber(sc.nextInt());
            users[i].setAccountBalance(sc.nextInt());
            users[i].setUsername(sc.next());
        }
        
        int searchAccNo = sc.nextInt();
        boolean found = false;
        
        for(int i = 0; i < n; i++) {
            if(users[i].getAccountNumber() == searchAccNo) {
                System.out.println(users[i].getAccountBalance());
                found = true;
                break;
            }
        }
        
        if(!found) {
            System.out.println("Account Number does not exist");
        }
        
        sc.close();
    }
}