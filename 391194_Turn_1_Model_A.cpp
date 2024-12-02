#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define the size of the hash table
const int TABLE_SIZE = 10;

struct Node {
    string key;
    Node* next;
    Node(string k) : key(k), next(nullptr) {}
};

class HashTable {
private:
    vector<Node*> table;

public:
    HashTable() : table(TABLE_SIZE) { }

    int hashFunction(string key) const {
        return std::hash<string>{}(key) % TABLE_SIZE;
    }

    void insert(string key) {
        int index = hashFunction(key);
        if (!table[index]) {
            table[index] = new Node(key);
        } else {
            Node* current = table[index];
            while (current != nullptr) {
                if (current->key == key) {
                    cout << "Key already exists." << endl;
                    return;
                }
                current = current->next;
            }
            table[index]->next = new Node(key);
        }
    }

    void search(string key) const {
        int index = hashFunction(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                cout << "Found: " << key << endl;
                return;
            }
            current = current->next;
        }
        cout << "Key not found." << endl;
    }

    ~HashTable() {
        for (auto* node : table) {
            while (node != nullptr) {
                auto* next = node->next;
                delete node;
                node = next;
            }
        }
    }
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
