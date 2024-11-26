#include <iostream>
#include <string>
#include <deque>
using namespace std;

// Define a MenuItem struct to hold the label and the corresponding action (command).
struct MenuItem {
    string label;
    int command;
};

// Class to manage the menu system using deque.
class MenuSystem {
public:
    void addMenuItem(const MenuItem& item) {
        menuItems.push_back(item);
    }

    void removeMenuItem(int command) {
        auto it = find_if(menuItems.begin(), menuItems.end(), [&](const MenuItem& mi) { return mi.command == command; });
        if (it != menuItems.end()) {
            menuItems.erase(it);
        }
    }

    void displayMenu() const {
        cout << "Menu:\n";
        for (size_t i = 0; i < menuItems.size(); ++i) {
            cout << i + 1 << ". " << menuItems[i].label << endl;
        }
        cout << "Enter your choice: ";
    }

    int getUserInput() const {
        int choice;
        cin >> choice;
        cin.ignore(); // Ignore newline after input
        return choice;
    }

    int handleUserAction(int command) {
        for (const auto& item : menuItems) {
            if (item.command == command) {
                // Implement logic for each command
                switch (command) {
                    case 1:
                        cout << "Opening file...\n";
                        break;
                    case 2:
                        cout << "Saving file...\n";
                        break;
                    case 3:
                        cout << "Adding new menu item...\n";
                        addMenuItem({"New Option", 4});
                        break;
                    case 4:
                        cout << "Executing new option...\n";
                        break;
                    case 5:
                        cout << "Removing menu item 'New Option'...\n";
                        removeMenuItem(4);
                        break;
                    case 6:
                        cout << "Exiting...\n";
                        return -1;
                    default:
                        cout << "Invalid command. Please try again.\n";
                }
                return 0;
            }
        }
        cout << "Invalid choice. Please try again.\n";
        return 0;
    }

private:
    deque<MenuItem> menuItems;
};

int main() {
    MenuSystem menuSystem;

    // Initial menu items
    MenuItem openFile({"Open File", 1});
    MenuItem saveFile({"Save File", 2});
    MenuItem addNewOption({"Add New Option", 3});

    menuSystem.addMenuItem(openFile);
    menuSystem.addMenuItem(saveFile);
    menuSystem.addMenuItem(addNewOption);

    int exitStatus = 0;
    while (exitStatus == 0) {
        menuSystem.displayMenu();
        int choice = menuSystem.getUserInput();
        exitStatus = menuSystem.handleUserAction(choice);
    }

    return 0;
}
