  #include <iostream>
  #include <chrono>
  #include <vector>
  #include <list>
  #include <set>
  #include <unordered_set>
  #include <map>
  #include <unordered_map>
  using namespace std;
  const size_t TEST_SIZE = 1'000'000; // One million elements
  template <typename Container>
  void benchmark_push_back(const string& name) {
    Container container;
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < TEST_SIZE; ++i) {
        container.push_back(i);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> duration = end - start;
    cout << name << ": push_back - " << duration.count() / 1e6 << " ms\n";
}
  template <typename Container>
  void benchmark_insert(const string& name) {
    Container container;
    for (size_t i = 0; i < TEST_SIZE / 2; ++i) {
        container.insert(randomElement(container.begin(), container.end()), i);
    }
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = TEST_SIZE / 2; i < TEST_SIZE; ++i) {
        container.insert(container.begin(), i);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> duration = end - start;
    cout << name << ": insert - " << duration.count() / 1e6 << " ms\n";
  }
  template <typename Key, typename Compare, typename Container>
  void benchmark_lower_bound(const string& name) {
    Container container;
    for (size_t i = 0; i < TEST_SIZE; ++i) {
        container.insert(i);
    }
   auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < TEST_SIZE; ++i) {
        container.lower_bound(i);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> duration = end - start;
   cout << name << ": lower_bound - " << duration.count() / 1e6 << " ms\n";
  }
  template <typename Container>
  Container& randomElement(typename Container::iterator start, typename Container::iterator end)
  {
    uniform_int_distribution<> random(dist(start), dist(end - 1));
    return *(start + random(g));
  }
  int main() {
   default_random_engine g(chrono::steady_clock::now().time_since_epoch().count());
    typedef int Key;
    typedef greater<Key> Compare;

    cout << "Benchmarking:\n";
    benchmark_push_back<vector<Key>>("vector");
    benchmark_insert<vector<Key>>("vector");
    benchmark_lower_bound<Key, Compare, set<Key, Compare>>("set (sorted)");
    benchmark_lower_bound<Key, Compare, unordered_set<Key, hash<Key>, equal_to<Key>>>("unordered_set (hash)");

   cout << "Simulated trading operations:\n";
   vector<Key> orders;
   orders.reserve(TEST_SIZE);
   /// Simulating order placement.
   for (size_t i = 0; i < TEST_SIZE; ++i) {
     orders.push_back(i);
   }

   /// Simulating order execution based on price tiers.
