#include <iostream>
#include <cassert>
#include <stdexcept>

class BankAccount {
public:
    BankAccount(double initial_balance) 
        : balance(initial_balance) {
        // Invariant: Balance should never be negative
        assert(balance >= 0);
    }

    void deposit(double amount) {
        // Precondition: Deposit amount must be positive
        if (amount <= 0) {
            throw std::invalid_argument("Deposit amount must be positive");
        }

        balance += amount;

        // Postcondition: Ensure the state with fund increases post transaction
        assert(balance >= 0);
    }

    void withdraw(double amount) {
        // Precondition: Withdraw amount must be positive and less than the current balance
        if (amount <= 0 || amount > balance) {
            throw std::invalid_argument("Withdraw amount must be positive and not exceed balance");
        }

        balance -= amount;

        // Postcondition: Ensure balance should remain non-negative
        assert(balance >= 0);
    }

    double checkBalance() const {
        return balance;
    }

private:
    double balance;
    // Invariant: Ensure balance is consistent
    void checkInvariant() const {
        assert(balance >= 0);
    }
};

int main() {
    try {
        BankAccount myAccount(100.0);

        myAccount.deposit(50.0);
        std::cout << "Balance after deposit: $" << myAccount.checkBalance() << std::endl;

        myAccount.withdraw(30.0);
        std::cout << "Balance after withdrawal: $" << myAccount.checkBalance() << std::endl;

        // This will throw an exception due to failed precondition
        myAccount.withdraw(150.0);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
