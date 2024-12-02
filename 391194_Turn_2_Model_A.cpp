#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Define the size of the hash table
const int TABLE_SIZE = 10;

class HashTable {
private:
    vector<vector<string>> table;

public:
    HashTable() : table(TABLE_SIZE, vector<string>()) { }

    int hashFunction(string key) const {
        return unordered_map<string, int>{{"apple", 0}, {"banana", 1}, {"orange", 2}, {"grape", 3}, {"cherry", 4}, {"kiwi", 5}, {"peach", 6}, {"lemon", 7}, {"mango", 8}, {"watermelon", 9}}[key];
    }

    void insert(string key) {
        int index = hashFunction(key);
        if (!find(table[index].begin(), table[index].end(), key)) {
            table[index].push_back(key);
        } else {
            cout << "Key already exists." << endl;
        }
    }

    void search(string key) const {
        int index = hashFunction(key);
        if (find(table[index].begin(), table[index].end(), key) != table[index].end()) {
            cout << "Found: " << key << endl;
        } else {
            cout << "Key not found." << endl;
        }
    }

    ~HashTable() { }
};

int main() {
    HashTable table;
    table.insert("apple");
    table.insert("banana");
    table.insert("orange");
    table.insert("banana"); // Duplicate key

    table.search("banana");
    table.search("grape");

    return 0;
}
