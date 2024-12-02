#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

const int TABLE_SIZE = 10;

// Simple hash function using modulo operator
int hashFunction(const string& key) {
    size_t hashValue = hash<string>{}(key);
    return hashValue % TABLE_SIZE;
}

class SingleTableHashTable {
private:
    vector<unordered_set<string>> table;

public:
    SingleTableHashTable() : table(TABLE_SIZE) {}

    void insert(const string& key) {
        int index = hashFunction(key);
        table[index].insert(key);
    }

    bool search(const string& key) const {
        int index = hashFunction(key);
        return table[index].find(key) != table[index].end();
    }

    void remove(const string& key) {
        int index = hashFunction(key);
        table[index].erase(key);
    }
};
 
int main() {
    SingleTableHashTable table;
    table.insert("apple");
    table.insert("banana");
    table.insert("orange");

    cout << "Search for 'banana': " << table.search("banana") << endl;  // Output: 1
    cout << "Search for 'grape': " << table.search("grape") << endl;   // Output: 0

    table.remove("banana");
    cout << "Search for 'banana' after removal: " << table.search("banana") << endl;  // Output: 0

    return 0;
}
