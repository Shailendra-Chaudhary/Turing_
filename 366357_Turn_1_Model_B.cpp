

```c++
#include <iostream>
#include <string>
#include <deque>
using namespace std;

// Define a MenuItem struct
struct MenuItem {
    string label;
    int command;
};

// A simple GUI class
class SimpleGUI {
public:
    void addMenuItem(const MenuItem& item);
    void removeMenuItem(int command);
    void displayMenu() const;
    int getUserInput() const;
private:
    deque<MenuItem> menuItems;
};

void SimpleGUI::addMenuItem(const MenuItem& item) {
    menuItems.push_back(item);
}

void SimpleGUI::removeMenuItem(int command) {
    for (auto it = menuItems.begin(); it != menuItems.end(); ++it) {
        if (it->command == command) {
            menuItems.erase(it);
            return;
        }
    }
}

void SimpleGUI::displayMenu() const {
    cout << "Menu:" << endl;
    for (size_t i = 0; i < menuItems.size(); ++i) {
        cout << i + 1 << ". " << menuItems[i].label << endl;
    }
    cout << "Enter your choice: ";
}

int SimpleGUI::getUserInput() const {
    int choice;
    cin >> choice;
    cin.ignore(); // Ignore newline after input
    return choice;
}

int main() {
    SimpleGUI gui;
    // Define some initial menu items
    MenuItem openFile = {"Open File", 1};
    MenuItem saveFile = {"Save File", 2};
    MenuItem exit = {"Exit", 3};

    gui.addMenuItem(openFile);
    gui.addMenuItem(saveFile);
    gui.addMenuItem(exit);

    bool continueRunning = true;
    while (continueRunning) {
        gui.displayMenu();
        int choice = gui.getUserInput();

        switch (choice) {
        case 1:
            cout << "Opening file..." << endl;
            // Add dynamic menu updates here based on the user action
            gui.removeMenuItem(2); // Remove "Save File" menu item after opening
            gui.addMenuItem({"Close File", 4}); // Add "Close File" menu item
            break;
        case 2:
            cout << "Saving file..." << endl;
            break;
        case 3:
            cout << "Goodbye!" << endl;
            continueRunning = false;
            break;
        case 4:
            cout << "Closing file..." << endl;
            // Add dynamic menu updates here based on the user action
            gui.removeMenuItem(4); // Remove "Close File" menu item after closing
            gui.addMenuItem(saveFile); // Add "Save File" menu item back
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
                  ```
