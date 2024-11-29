#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <algorithm>
#include <chrono>
using namespace std;

// A function to generate random integers between min and max
int randInt(int min, int max) {
    return std::rand() % (max - min + 1) + min;
}
 
// Function to insert n elements into a container 
template <typename Container>
void insert_elements(Container& cont, int n) {
    for (int i = 0; i < n; ++i) {
        cont.insert(randInt(0, n));
    }
}
 
//Function to search an element in a container
template <typename Container>
bool search_element(Container& cont, int element) {
    return cont.find(element) != cont.end();
}

// Function to calculate the average time taken for a specific function
template <typename T, typename F>
double time_execution(T&& cont, F&& func, int num_elements) {
    //Using steady_clock for high precision timing
    using namespace std::chrono;
    auto start = steady_clock::now();

    // Execute the function with the provided container and parameters
    func(cont, num_elements);

    auto end = steady_clock::now();

    // Calculate the time taken in milliseconds
    duration<double, milli> duration = end - start;
    return duration.count();
}

int main()
{
    const int num_elements = 1000000;

    // Initialize containers
    std::vector<int> vec;
    std::set<int> st;
    std::unordered_set<int> ust;
    std::unordered_map<int, int> umap;
    std::deque<int> dq;

    // Insert elements into each container and calculate the average insertion time
    std::cout << "INSERTION TIME:\n";
    double insertion_time_vec = time_execution(vec, insert_elements<std::vector<int>>, num_elements);
    std::cout << "std::vector: " << insertion_time_vec << " ms\n";
    double insertion_time_st = time_execution(st, insert_elements<std::set<int>>, num_elements); 
    std::cout << "std::set: " << insertion_time_st << " ms\n";
    double insertion_time_ust = time_execution(ust, insert_elements<std::unordered_set<int>>, num_elements);
    std::cout << "std::unordered_set: " << insertion_time_ust << " ms\n";
    double insertion_time_umap = time_execution(umap, insert_elements<std::unordered_map<int, int>>, num_elements);
    std::cout << "std::unordered_map: " << insertion_time_umap << " ms\n"; 
    double insertion_time_dq = time_execution(dq, insert_elements<std::deque<int>>, num_elements); 
    std::cout << "std::deque: " << insertion_time_dq << " ms\n"; 

   // reset the containers
    vec.clear();
    st.clear();
    ust.clear();
    umap.clear();
    dq.clear();

    // Search random element in each container and calculate the average search time
    std::cout << "\nSEARCH TIME:\n";
    for (int i = 0; i < num_elements; i++) {
        int element = randInt(0, num_elements);
        insert_elements(ust, 1); // using unordered_set for consistent insert time
