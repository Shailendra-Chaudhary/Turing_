#include <iostream>
#include <vector>
using namespace std;

class FinancialProduct {
public:
    virtual ~FinancialProduct() = default;

    virtual double calculateValue() const = 0;
    virtual void add(FinancialProduct* product) {
        cerr << "Error: Can only add to Portfolios." << endl;
    }
    virtual void remove(FinancialProduct* product) {
        cerr << "Error: Can only remove from Portfolios." << endl;
    }
    virtual bool isPortfolio() const { return false; }

    virtual string toString() const = 0;
};

class Asset : public FinancialProduct {
private:
    double value;

public:
    Asset(double value) : value(value) {}

    double calculateValue() const override {
        return value;
    }

    string toString() const override {
        return "Asset: $" + to_string(value);
    }
};

class Portfolio : public FinancialProduct {
private:
    vector<FinancialProduct*> products;

public:
    ~Portfolio() {
        for (auto product : products) {
            delete product;
        }
    }

    void add(FinancialProduct* product) override {
        products.push_back(product);
    }

    void remove(FinancialProduct* product) override {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (*it == product) {
                delete *it;
                products.erase(it);
                return;
            }
        }
        cerr << "Product not found in Portfolio." << endl;
    }

    double calculateValue() const override {
        double total = 0;
        for (auto product : products) {
            total += product->calculateValue();
        }
        return total;
    }
    
    bool isPortfolio() const override {
        return true;
    }

    string toString() const override {
        string result = "Portfolio:\n";
        for (auto product : products) {
            result += "  " + product->toString() + "\n";
        }
        return result;
    }
};

int main() {
    FinancialProduct* stock = new Asset(100.0);
    FinancialProduct* bond = new Asset(50.0);
    FinancialProduct* portfolio1 = new Portfolio();
    FinancialProduct* portfolio2 = new Portfolio();

    portfolio1->add(stock);
    portfolio1->add(bond);

    portfolio2->add(portfolio1);
    portfolio2->add(new Asset(75.0));

    cout << "Portfolio 1:" << endl;
    cout << portfolio1->toString() << endl;
    cout << "Value of Portfolio 1: $" << portfolio1->calculateValue() << endl;

    cout << "\nPortfolio 2:" << endl;
    cout << portfolio2->toString() << endl;
    cout << "Value of Portfolio 2: $" << portfolio2->calculateValue() << endl;

    portfolio2->remove(stock);

    cout << "\nPortfolio 2 after removing stock:" << endl;
    cout << portfolio2->toString() << endl;
    cout << "Value of Portfolio 2: $" << portfolio2->calculateValue() << endl;

    // Clean up dynamic memory
    delete stock;
    delete bond;
    delete portfolio1;
    delete portfolio2;
    return 0;
}
