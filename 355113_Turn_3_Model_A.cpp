#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <tbb/tick_count.h>

#include <random>
#include <ctime>
#include <algorithm>

struct Trade {
    int timestamp;
    double price;
    int size;
};

template<typename Container>
void simulateTrading(Container& container, int numTrades) {
    // Simulate generating random trade data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> timeDist(1, 100000);
    std::uniform_real_distribution<> priceDist(1.0, 1000.0);
    std::uniform_int_distribution<> sizeDist(1, 10000);
    
    for (int i = 0; i < numTrades; ++i) {
        Trade trade;
        trade.timestamp = timeDist(gen);
        trade.price = priceDist(gen);
        trade.size = sizeDist(gen);
        container.push_back(trade);
    }

    // Simulate sorting the container by timestamp for order book management
    std::sort(container.begin(), container.end(), [](const Trade& a, const Trade& b) {
        return a.timestamp < b.timestamp;
    });

    // Simulate processing the top trade in the order book
    for (const Trade& trade : container) {
    }
}

template<typename Container>
void benchmark(const std::string& name, Container& container, int numTrades) {
    tbb::tick_count t1 = tbb::tick_count::now();
    simulateTrading(container, numTrades);
    tbb::tick_count t2 = tbb::tick_count::now();
    double elapsed = double(t2 - t1) / tbb::tick_count::rate;

    std::cout << name << ": " << numTrades << " trades, " << elapsed << " seconds" << std::endl;
}

int main() {
    const int numTrades = 1000000;

    std::vector<Trade> vectorTrades;
    std::deque<Trade> dequeTrades;
    std::list<Trade> listTrades;
    std::set<Trade> setTrades;
    std::unordered_set<Trade> unorderedSetTrades;
    std::map<int, Trade> mapTrades;
    std::unordered_map<int, Trade> unorderedMapTrades;

    std::cout << "Benchmarking STL Containers for Simulated Trading:" << std::endl;
    benchmark("std::vector", vectorTrades, numTrades);
    benchmark("std::deque", dequeTrades, numTrades);
    benchmark("std::list", listTrades, numTrades);
    benchmark("std::set", setTrades, numTrades);
    benchmark("std::unordered_set", unorderedSetTrades, numTrades);
    benchmark("std::map", mapTrades, numTrades);
    benchmark("std::unordered_map", unorderedMapTrades, numTrades);

    return 0;
}
