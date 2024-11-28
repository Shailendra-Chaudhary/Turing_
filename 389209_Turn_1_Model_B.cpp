#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

// Case 1: Simple array of integers
void example1() {
    vector<int> myArray;
    myArray.push_back(1);
    myArray.push_back(8);
    myArray.push_back(4);

    // Displaying elements using iterator
    vector<int>::iterator it;
    for (it = myArray.begin(); it != myArray.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Using STL algorithms
    sort(myArray.begin(), myArray.end());
    cout << "Sorted array: ";
    for_each(myArray.begin(), myArray.end(), [](int i) { cout << i << " "; });
    cout << endl;
}

// Case 2: Doubly linked list of strings
void example2() {
    list<string> myList;
    myList.push_back("apple");
    myList.push_back("banana");
    myList.push_back("cherry");

    // Displaying elements using iterator
    list<string>::iterator it;
    for (it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Using STL algorithms
    reverse(myList.begin(), myList.end());
    cout << "Reversed list: ";
    for_each(myList.begin(), myList.end(), [](string str) { cout << str << " "; });
    cout << endl;
}

// Case 3: Set of unique characters (no duplicates)
void example3() {
    set<char> mySet;
    string input = "hello";
    for (char ch : input) {
        mySet.insert(ch);
    }

    // Displaying elements using iterator
    set<char>::iterator it;
    for (it = mySet.begin(); it != mySet.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

// Case 4: Map from student IDs to their names
void example4() {
    map<int, string> studentMap;
    studentMap[1] = "Alice";
    studentMap[2] = "Bob";
    studentMap[3] = "Charlie";

    // Displaying elements using iterator
    map<int, string>::iterator it;
    for (it = studentMap.begin(); it != studentMap.end(); ++it) {
        cout << "Student ID: " << it->first << ", Name: " << it->second << endl;
    }
    
    // Using key to find a value
    int studentId = 2;
    auto found = studentMap.find(studentId);
    if (found != studentMap.end()) {
        cout << "Found student with ID " << studentId << ": " << found->second << endl;
    } else {
        cout << "Student with ID " << studentId << " not found." << endl;
    }
}

// Case 5: Unordered set for fast lookups and insertions (no duplicates)
void example5() {
    unordered_set<int> myUnorderedSet;
    myUnorderedSet.insert(10);
    myUnorderedSet.insert(20);
    myUnorderedSet.insert(30);

    // Displaying elements using iterator
    unordered_set<int>::iterator it;
    for (it = myUnorderedSet.begin(); it != myUnorderedSet.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Checking if an element exists
    int element = 20;
    if (myUnorderedSet.find(element) != myUnorderedSet.end()) {
        cout << "Element " << element << " found." << endl;
    } else {
        cout << "Element " << element << " not found." << endl;
    }
}

// Case 6: Unordered map for fast lookups and insertions (keys are unique)
