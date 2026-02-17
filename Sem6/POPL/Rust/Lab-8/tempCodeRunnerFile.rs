#[derive(Debug)]
enum AccountType {
    Savings,
    Current,
}

#[derive(Debug)]
struct Account {
    id: u32,
    holder: String,
    balance: f64,
    acc_type: AccountType,
}

impl Account {
    fn new(id: u32, holder: String, balance: f64, acc_type: AccountType) -> Self {
        Account {
            id,
            holder,
            balance,
            acc_type,
        }
    }

    fn display_account_details(&mut self) {
        match self.acc_type {
            AccountType::Savings => {
                println!("--- Savings Account ---");
                let interest = self.balance * 0.05;
                self.balance += interest;
                println!("Interest of 5% (${:.2}) applied.", interest);
            }
            AccountType::Current => {
                println!("--- Current Account ---");
                if self.balance < 1000.0 {
                    self.balance -= 100.0;
                    println!("Service charge of $100.00 applied due to low balance.");
                } else {
                    println!("No service charges applied.");
                }
            }
        }
        println!("Holder: {}\nUpdated Balance: ${:.2}\n", self.holder, self.balance);
    }
}

#[derive(Debug)]
struct Bank {
    accounts: Vec<Account>,
}

impl Bank {
    fn new() -> Self {
        Bank { accounts: vec![] }
    }

    fn add_account(&mut self, account: Account) {
        self.accounts.push(account);
    }

    fn process_accounts(&mut self) {
        for account in &mut self.accounts {
            account.display_account_details();
        }
    }
}

fn main() {
    let mut bank = Bank::new();

    let savings = Account::new(1, String::from("Alice"), 1000.0, AccountType::Savings);
    
    let current = Account::new(2, String::from("Bob"), 500.0, AccountType::Current);

    bank.add_account(savings);
    bank.add_account(current);

    bank.process_accounts();
}