#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

int main()
{
    // Single-table hashing using std::unordered_map (Chained Hashing)
    unordered_map<int, string> single_hash;

    // Insert elements into the hash table
    single_hash[1] = "One";
    single_hash[2] = "Two";
    single_hash[10] = "Ten";  // Collision happens here as hash of 10 and 2 is same.
    single_hash[3] = "Three";
    single_hash[20] = "Twenty"; // Collision happens here as hash of 20 and 10 is same.

    // ***Pros of Single-table Hashing:***
    
    // Simple to implement
    // Good for small to medium-sized data sets
    // No need to manage multiple hash tables
    
    // ***Cons of Single-table Hashing:***

    // Performance degradation with collisions (especially in larger data sets)
    // This can lead to uneven load distribution across buckets, affecting insertion and search performance.
    // Requires rehashing when the load factor increases significantly (collisions worsen).
    
    cout<<"Single table hashing: "<<endl;
    for (auto& key_value : single_hash) 
    {
        cout << "Key: " << key_value.first << ", Value: " << key_value.second << endl;
    }
    
    return 0;
}  
