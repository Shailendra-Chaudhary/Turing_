#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include <algorithm>

class Student {
public:
    int id;
    std::string name;

    Student(int id, const std::string& name) : id(id), name(name) {}

    bool operator<(const Student& other) const {
        return id < other.id;
    }
};

void evaluateContainer(const std::string& containerName, std::vector<Student>& data) {
    std::cout << "Using " << containerName << ":\n";

    // Add students
    for (int i = 1; i <= 10; ++i) {
        data.emplace_back(i, "Student " + std::to_string(i));
    }
    std::cout << "  Size: " << data.size() << "\n";

    // Search by ID
    int searchId = 5;
    auto it = std::find_if(data.begin(), data.end(), [searchId](const Student& student) {
        return student.id == searchId;
    });
    if (it != data.end()) {
        std::cout << "  Found student with ID " << searchId << ": " << it->name << "\n";
    } else {
        std::cout << "  Student with ID " << searchId << " not found.\n";
    }

    // Sort by name
    std::sort(data.begin(), data.end(), [](const Student& a, const Student& b) {
        return a.name < b.name;
    });

    // List students by name
    std::cout << "  Students by name:\n";
    for (const auto& student : data) {
        std::cout << student.name << "\n";
    }

    std::cout << "--------------------\n";
}

int main() {
    // Using std::vector
    std::vector<Student> vectorStudents;
    evaluateContainer("std::vector", vectorStudents);

    // Using std::deque
    std::deque<Student> dequeStudents;
    evaluateContainer("std::deque", dequeStudents);

    // Using std::list
    std::list<Student> listStudents;
    evaluateContainer("std::list", listStudents);

    // Using std::map
    std::map<int, Student> mapStudents;
    evaluateContainer("std::map", mapStudents);

    // Using std::unordered_map
    std::unordered_map<int, Student> unorderedMapStudents;
    evaluateContainer("std::unordered_map", unorderedMapStudents);

    // Using std::set
    std::set<Student> setStudents;
    evaluateContainer("std::set", setStudents);

    return 0;
}
