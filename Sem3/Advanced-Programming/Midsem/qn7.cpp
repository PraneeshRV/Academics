//program to manage a bank account using classes and objects
#include <iostream>
using namespace std;

// BankAccount class
class BankAccount {
    
    private:
        int accountNumber;
        string accountHolderName;
        float balance;
        
    public:
    //Default constructor
    BankAccount(){
            accountNumber =0;
            accountHolderName = "null";
            balance =0;
    }
    
    //parameterized constructor
        BankAccount(int _accountNumber, string _accountHolderName, float _balance){
            accountNumber = _accountNumber;
            accountHolderName = _accountHolderName;
            balance = _balance;
        }
    //display function
        void display(){
            cout<<"Account Number : "<<accountNumber<<endl;
            cout<<"Name: "<<accountHolderName<<endl;
            cout<<"Balance: "<<"$"<<balance<<endl;
        }
    //deposit function
        void deposit(){
            float dep;
            cout<<"Please enter the amount to be deposited"<<endl;
            cin>>dep;
            // Check if deposit amount is valid
            if (dep<=0){
                cout<<"You cannot deposit a negative value or 0, please try again with a non-zero positive value"<<endl;
            }
            else{
            balance = balance + dep;
            cout<<"Deposit successful, your current balance is: "<<"$"<<balance<<endl;
            }
        }
    //withdraw function
        void withdraw(){
            float wit;
            cout<<"Please enter the amount to be withdrawn"<<endl;
            cin>>wit;
            // Check if withdrawal amount is valid
            if (wit>balance){
                cout<<"You cannot withdraw more than what you have in your balance, your current balance is: "<<balance<<endl;
            }
            else{
            balance = balance -wit;
            cout<<"Withdraw successful, your current balance is: "<<"$"<<balance<<endl;
            }
        }
    //calculate Interest function
    void calculateInterest(){
        float ir = 7.2, in = balance*ir/100;
        cout<<"The current interest rate is: "<<ir<<"%"<<endl;
        cout<<"The interest on your balance "<<"$"<<in<<" has been added to your balance successfully"<<endl;
        balance = balance + in;
        cout<<"Your current balance is: "<<"$"<<balance<<endl;
    }
        
};

int main() {
    int opt;
    BankAccount b0; // Default constructor
    BankAccount b1(23036,"Praneesh R V",420.51); // Parameterized constructor
    
    do {
        // Display menu
        cout << "\nWelcome" << endl;
        cout << "Enter Your option:" << endl;
        cout << "1. Display details" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Calculate interest" << endl;
        cout << "5. Exit" << endl;
        cin >> opt;

        // Process user's choice
        switch(opt) {
            case 1:
                b1.display();
                break;
            case 2:
                b1.deposit();
                break;
            case 3:
                b1.withdraw();
                break;
            case 4:
                b1.calculateInterest();
                break;
            case 5:
                cout << "Thank you for using our services. Goodbye!" << endl;
                break;
            default:
                cout << "Please enter a valid input" << endl;
        }
    } while (opt != 5);
    
    return 0;
}