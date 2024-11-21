#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

// Structure to represent a trade order
struct TradeOrder {
    int orderId;
    string symbol;
    bool isBuy;
    double price;
    int quantity;
};

// Function to generate random trade orders
vector<TradeOrder> generateRandomOrders(int numOrders) {
    vector<TradeOrder> orders;
    default_random_engine generator;
    uniform_int_distribution<> orderIdDist(1000, 9999);
    uniform_string_distribution<> symbolDist({"AAPL", "MSFT", "GOOG", "FB", "AMZN"});
    uniform_int_distribution<> isBuyDist(0, 1);
    uniform_real_distribution<> priceDist(10.0, 1000.0);
    uniform_int_distribution<> quantityDist(1, 1000);

    for (int i = 0; i < numOrders; ++i) {
        TradeOrder order;
        order.orderId = orderIdDist(generator);
        order.symbol = symbolDist(generator);
        order.isBuy = isBuyDist(generator);
        order.price = priceDist(generator);
        order.quantity = quantityDist(generator);
        orders.push_back(order);
    }

    return orders;
}

// Function to insert orders at the back of the container
template <typename Container>
void insertOrders(Container& ordersContainer, const vector<TradeOrder>& orders) {
    for (const TradeOrder& order : orders) {
        ordersContainer.push_back(order);
    }
}

template <typename Container>
void testPerformance(const string& containerName, const vector<TradeOrder>& orders) {
    auto container = Container();

    // Measure the time to insert orders
    auto start = chrono::high_resolution_clock::now();
    insertOrders(container, orders);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, std::nano> duration = end - start;
    double executionTime = duration.count() / 1'000'000; // Convert to milliseconds

    cout << containerName << " performance:" << endl;
    cout << "   Execution Time: " << executionTime << " ms" << endl;
    cout << "   Order Container Size: " << container.size() << endl << endl;
}

int main() {
    const int numOrders = 1'000'000;  // Generate 1 million random orders
    vector<TradeOrder> orders = generateRandomOrders(numOrders);

    cout << "STL Container Performance Comparison:" << endl;
    testPerformance<vector<TradeOrder>>("vector", orders);
    testPerformance<deque<TradeOrder>>("deque", orders);

    return 0;
}
