#include <iostream>
#include <string>
using namespace std;

class String {
private:
    string data;

public:
    // Constructor
    String(const string &str = "") : data(str) {}

    // Overloading == operator for equality check
    bool operator==(const String &other) const {
        return data == other.data;
    }

    // Overloading != operator for inequality check
    bool operator!=(const String &other) const {
        return !(*this == other);
    }

    // Overloading < operator for less than check
    bool operator<(const String &other) const {
        return data < other.data;
    }

    // Overloading > operator for greater than check
    bool operator>(const String &other) const {
        return other < *this;
    }

    // Overloading <= operator for less than or equal to check
    bool operator<=(const String &other) const {
        return !(*this > other);
    }

    // Overloading >= operator for greater than or equal to check
    bool operator>=(const String &other) const {
        return !(*this < other);
    }

    // Overloading logical AND operator
    bool operator&&(const String &other) const {
        return !data.empty() && !other.data.empty();
    }

    // Overloading logical OR operator
    bool operator||(const String &other) const {
        return !data.empty() || !other.data.empty();
    }

    // Overloading ! operator for logical negation
    bool operator!() const {
        return data.empty();
    }

    // Assigning a new string
    String& operator=(const string &str) {
        data = str;
        return *this;
    }

    // Printing the String
    void print() const {
        cout << data << endl;
    }
};

int main() {
    String str1("hello");
    String str2("world");
    String str3("");

    // Using overloaded logical operators
    cout << "str1 == str2: " << (str1 == str2) << endl;
    cout << "str1 != str2: " << (str1 != str2) << endl;
    cout << "str1 < str2: " << (str1 < str2) << endl;
    cout << "str1 > str2: " << (str1 > str2) << endl;
    cout << "str1 <= str2: " << (str1 <= str2) << endl;
    cout << "str1 >= str2: " << (str1 >= str2) << endl;
    cout << "str1 && str2: " << (str1 && str2) << endl;
    cout << "str1 || str2: " << (str1 || str2) << endl;
    cout << "!str1: " << (!str1) << endl;
    cout << "!str3: " << (!str3) << endl;

    // Printing Strings
    str1.print();
    str2.print();
    str3.print();

    return 0;
}
