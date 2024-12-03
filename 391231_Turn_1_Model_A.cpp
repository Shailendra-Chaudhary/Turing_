#include <iostream>
#include <cassert>

class BankAccount {
private:
    double balance;

    // Invariant: Balance must always be non-negative
    void checkInvariant() const {
        assert(balance >= 0, "Balance must be non-negative");
    }

public:
    BankAccount(double initialBalance) : balance(initialBalance) {
        checkInvariant();
    }

    // Precondition: Deposit amount must be non-negative
    void deposit(double amount) {
        assert(amount >= 0, "Deposit amount must be non-negative");
        balance += amount;
        checkInvariant();
    }

    // Precondition: Withdrawal amount must be non-negative and less than or equal to available balance
    void withdraw(double amount) {
        assert(amount >= 0, "Withdrawal amount must be non-negative");
        assert(amount <= balance, "Withdrawal amount must not exceed available balance");
        balance -= amount;
        checkInvariant();
    }

    // Postcondition: Returns the current balance
    double getBalance() const {
        checkInvariant();
        return balance;
    }
};

int main() {
    BankAccount account(100.0);
    account.deposit(50.0);
    std::cout << "Balance after deposit: " << account.getBalance() << std::endl;
    account.withdraw(30.0);
    std::cout << "Balance after withdrawal: " << account.getBalance() << std::endl;

    // Uncommenting the following line will cause an assertion failure
    // account.withdraw(200.0);

    return 0;
}
