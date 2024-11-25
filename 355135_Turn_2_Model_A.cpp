#include <iostream>
#include <string>
#include <vector>

class FinancialProduct {
public:
    virtual ~FinancialProduct() = default;

    virtual double calculateValue() const = 0;
    virtual void print() const = 0;

    virtual void add(FinancialProduct* product) {
        throw std::runtime_error("Operation not allowed for this type of FinancialProduct");
    }

    virtual void remove(FinancialProduct* product) {
        throw std::runtime_error("Operation not allowed for this type of FinancialProduct");
    }
};

class Asset : public FinancialProduct {
private:
    std::string name;
    double price;
    int quantity;

public:
    Asset(const std::string& name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}

    double calculateValue() const override {
        return price * quantity;
    }

    void print() const override {
        std::cout << name << " (Asset): $" << calculateValue() << std::endl;
    }
};

class Bond : public FinancialProduct {
private:
    std::string name;
    double faceValue;
    double couponRate;
    int yearsToMaturity;

public:
    Bond(const std::string& name, double faceValue, double couponRate, int yearsToMaturity)
        : name(name), faceValue(faceValue), couponRate(couponRate), yearsToMaturity(yearsToMaturity) {}

    double calculateValue() const override {
        // Simple bond value calculation (you can enhance this for more complex calculations)
        return faceValue;
    }

    void print() const override {
        std::cout << name << " (Bond): $" << calculateValue() << std::endl;
    }
};

class Portfolio : public FinancialProduct {
private:
    std::string name;
    std::vector<FinancialProduct*> products;

public:
    Portfolio(const std::string& name) : name(name) {}

    ~Portfolio() {
        for (auto product : products) {
            delete product;
        }
    }

    void add(FinancialProduct* product) override {
        products.push_back(product);
    }

    void remove(FinancialProduct* product) override {
        auto it = std::find(products.begin(), products.end(), product);
        if (it != products.end()) {
            delete *it;
            products.erase(it);
        } else {
            throw std::runtime_error("Product not found in the portfolio");
        }
    }

    double calculateValue() const override {
        double totalValue = 0.0;
        for (const auto& product : products) {
            totalValue += product->calculateValue();
        }
        return totalValue;
    }

    void print() const override {
        std::cout << name << " (Portfolio):\n";
        for (const auto& product : products) {
            product->print();
        }
        std::cout << "Total value of " << name << ": $" << calculateValue() << std::endl;
    }
};

int main() {
    FinancialProduct* appleStock = new Asset("Apple", 145.0, 100);
    FinancialProduct* googleStock = new Asset("Google", 2700.0, 50);
    FinancialProduct* bondA = new Bond("Bond A", 1000, 0.05, 5);

    FinancialProduct* techPortfolio = new Portfolio("Tech Portfolio");
    techPortfolio->add(appleStock);
    techPortfolio->add(googleStock);

    FinancialProduct* fixedIncomePortfolio = new Portfolio("Fixed Income Portfolio");
    fixedIncomePortfolio->add(bondA);

    FinancialProduct* retirementPortfolio = new Portfolio("Retirement Portfolio");
    retirementPortfolio->add(techPortfolio);
    retirementPortfolio->add(fixedIncomePortfolio);

    try {
        retirementPortfolio->add(new Asset("Dummy Asset", 0.0, 0));  // Demo adding to a Portfolio (allowed)
        appleStock->add(new Asset("Dummy Asset 2", 0.0, 0));  // Demo adding to an Asset (not allowed, throws error)
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    retirementPortfolio->print();

    // Clean up memory
    delete appleStock;
    delete googleStock;
    delete bondA;
    delete techPortfolio;
    delete fixedIncomePortfolio;
    delete retirementPortfolio;

    return 0;
}
 
