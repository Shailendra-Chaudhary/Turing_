#include <iostream>
#include <cassert>

class Account {
public:
    Account(double initial_balance) : balance(initial_balance) {
        // Invariant: Balance should never be negative
        assert(balance >= 0);
    }

    void deposit(double amount) {
        // Precondition: Deposit amount must be positive
        assert(amount > 0);

        balance += amount;

        // Postcondition: Balance should be greater or equal to amount
        assert(balance >= amount);
    }

    void withdraw(double amount) {
        // Precondition: Withdraw amount must be positive and <= balance
        assert(amount > 0 && balance >= amount);

        balance -= amount;

        // Postcondition: Balance should not be negative
        assert(balance >= 0);
    }

    double getBalance() const {
        return balance;
    }

private:
    double balance;
};

int main() {
    Account myAccount(100);

    myAccount.deposit(50);
    std::cout << "Balance after deposit: $" << myAccount.getBalance() << std::endl;

    myAccount.withdraw(30);
    std::cout << "Balance after withdrawal: $" << myAccount.getBalance() << std::endl;

    // Uncommenting this line will cause the program to abort since the precondition fails
    // myAccount.withdraw(150);
    
    return 0;
}
