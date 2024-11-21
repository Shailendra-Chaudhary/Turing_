#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>

#include <iomanip>

const int NUM_TRADES = 1000000;
const int MAX_TRADE_ID = 10000000;

using namespace std::chrono;

template <typename Container>
void measureInsertionTime(Container& container) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, MAX_TRADE_ID);

    auto start = high_resolution_clock::now();

    for (int i = 0; i < NUM_TRADES; ++i) {
        int tradeId = dis(gen);
        container.push_back({tradeId, i});
    }

    auto end = high_resolution_clock::now();
    duration<double, nano> duration = end - start;
    cout << "Insertion time for " << typeid(container).name() << ": " << duration.count() << " ns" << endl;
}

template <typename Container>
void measureAccessTime(const Container& container) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, MAX_TRADE_ID);

    auto start = high_resolution_clock::now();

    for (int i = 0; i < NUM_TRADES; ++i) {
        int tradeId = dis(gen);
        int _ = container.at({tradeId, 0}).second;
    }

    auto end = high_resolution_clock::now();
    duration<double, nano> duration = end - start;
    cout << "Access time for " << typeid(container).name() << ": " << duration.count() << " ns" << endl;
}

int main() {
    cout << "Benchmarking STL Containers for High-Frequency Trading:" << endl;

    cout << "Vector:" << endl;
    vector<pair<int, int>> tradeVector;
    measureInsertionTime(tradeVector);
    measureAccessTime(tradeVector);

    cout << "\nDeque:" << endl;
    deque<pair<int, int>> tradeDeque;
    measureInsertionTime(tradeDeque);
    measureAccessTime(tradeDeque);

    cout << "\nUnordered Map:" << endl;
    unordered_map<int, int> tradeMap;
    measureInsertionTime(tradeMap);
    measureAccessTime(tradeMap);

    return 0;
}
