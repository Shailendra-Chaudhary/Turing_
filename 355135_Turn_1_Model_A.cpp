#include <iostream>
#include <vector>
#include <string>

class FinancialProduct {
public:
    virtual ~FinancialProduct() = default;
    virtual double value() const = 0;
    virtual void add(const FinancialProduct* product) {
        // This method should only be in the Portfolio class
        (void)product;
        throw std::runtime_error("Cannot add product to an atomic Asset.");
    }
    virtual const std::string& name() const = 0;
};

class Asset : public FinancialProduct {
private:
    std::string name_;
    double price_;
    int quantity_;

public:
    Asset(const std::string& name, double price, int quantity)
        : name_(name), price_(price), quantity_(quantity) {}

    ~Asset() override = default;

    double value() const override {
        return price_ * quantity_;
    }

    const std::string& name() const override {
        return name_;
    }
};

class Portfolio : public FinancialProduct {
private:
    std::vector<const FinancialProduct*> children_;
    std::string name_;

public:
    Portfolio(const std::string& name) : name_(name) {}

    ~Portfolio() override {
        for (const FinancialProduct* child : children_) {
            delete child;
        }
    }

    double value() const override {
        double total = 0.0;
        for (const FinancialProduct* child : children_) {
            total += child->value();
        }
        return total;
    }

    void add(const FinancialProduct* product) override {
        children_.push_back(product);
    }
    
    const std::string& name() const override {
        return name_;
    }
};

int main() {
    std::cout << "Creating Financial Products..." << std::endl;
    const FinancialProduct* stockA = new Asset("Stock A", 100.0, 10);
    const FinancialProduct* stockB = new Asset("Stock B", 50.0, 20);
    const FinancialProduct* bond = new Asset("Bond", 1000.0, 1);

    std::cout << "Creating Portfolios..." << std::endl;
    Portfolio* portfolio1 = new Portfolio("Equity Portfolio");
    portfolio1->add(stockA);
    portfolio1->add(stockB);

    Portfolio* portfolio2 = new Portfolio("Fixed Income Portfolio");
    portfolio2->add(bond);

    Portfolio* grandPortfolio = new Portfolio("Grand Portfolio");
    grandPortfolio->add(portfolio1);
    grandPortfolio->add(portfolio2);

    std::cout << "\nCalculating Values..." << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Stock A: " << stockA->value() << std::endl;
    std::cout << "Stock B: " << stockB->value() << std::endl;
    std::cout << "Bond:    " << bond->value() << std::endl;
    std::cout << "Equity Portfolio: " << portfolio1->value() << std::endl;
    std::cout << "Fixed Income Portfolio: " << portfolio2->value() << std::endl;
    std::cout << "Grand Portfolio: " << grandPortfolio->value() << std::endl;

    std::cout << "\nDeleting products (memory will be deallocated automatically due to smart pointers)" << std::endl;

    return 0;
}
