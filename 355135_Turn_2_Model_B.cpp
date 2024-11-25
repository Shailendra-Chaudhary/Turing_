#include <iostream>
#include <vector>
#include <string>

using namespace std;

class FinancialProduct {
public:
    virtual ~FinancialProduct() = default;

    virtual double calculateValue() const = 0;
    virtual double calculateDividend() const = 0;
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
protected:
    string name;

public:
    Asset(const string& name) : name(name) {}

    string getName() const { return name; }
};

class Stock : public Asset {
private:
    double value;
    double dividendYield;

public:
    Stock(const string& name, double value, double dividendYield) : Asset(name), value(value), dividendYield(dividendYield) {}

    double calculateValue() const override {
        return value;
    }

    double calculateDividend() const override {
        return value * dividendYield;
    }

    string toString() const override {
        return "Stock: " + name + " ($" + to_string(value) + ", Dividend Yield: " + to_string(dividendYield * 100) + "%)";
    }
};

class Bond : public Asset {
private:
    double value;
    double couponRate;
    int maturityYears;

public:
    Bond(const string& name, double value, double couponRate, int maturityYears) 
        : Asset(name), value(value), couponRate(couponRate), maturityYears(maturityYears) {}

    double calculateValue() const override {
        return value;
    }

    double calculateDividend() const override {
        return value * couponRate;
    }

    string toString() const override {
        return "Bond: " + name + " ($" + to_string(value) + ", Coupon Rate: " + to_string(couponRate * 100) + "%, Maturity: " + to_string(maturityYears) + " years)";
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

    double calculateDividend() const override {
        double totalDividend = 0;
        for (auto product : products) {
            totalDividend += product->calculateDividend();
        }
        return totalDividend;
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
    FinancialProduct* stock1 = new Stock("AAPL", 145.0, 0.015);
    FinancialProduct* stock2 = new Stock("MSFT", 270.0, 0.01);
    FinancialProduct* bond1 = new Bond("US10Y", 1000.0, 0.025, 10);
    FinancialProduct* bond2 = new Bond("GER30Y", 1000.0, 0.018, 30);

    FinancialProduct* portfolio1 = new Portfolio();
    FinancialProduct* portfolio2 = new Portfolio();

    portfolio1->add(stock1);
    portfolio1->add(bond1);

    portfolio2->add(stock2);
    portfolio2->add(bond2);
    portfolio2->add(portfolio1);

    cout << "Portfolio 1:" << endl;
    cout << portfolio1->toString() << endl;
    cout << "Value of Portfolio 1: $" << portfolio1->calculateValue() << endl;
    cout << "Dividend of Portfolio 1: $" << portfolio1->calculateDividend() << endl;

    cout << "\nPortfolio 2:" << endl;
    cout << portfolio2->toString() << endl;
    cout << "Value of Portfolio 2: $" << portfolio2->calculateValue() << endl;
    cout << "Dividend of Portfolio 2: $" << portfolio2->calculateDividend() << endl;

    // Clean up dynamic memory
    delete stock1;
    delete stock2;
    delete bond1;
    delete bond2;
    delete portfolio1;
    delete portfolio2;

    return 0;
}
