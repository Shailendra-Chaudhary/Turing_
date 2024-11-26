#include <iostream>
#include <deque>
#include <string>

class Menu {
private:
    std::deque<std::string> options;

public:
    void addOption(const std::string& option) {
        options.push_back(option);
        std::cout << "Option added: " << option << std::endl;
    }

    void removeOption(int index) {
        if (index >= 0 && index < options.size()) {
            std::string removedOption = options[index];
            options.erase(options.begin() + index);
            std::cout << "Option removed: " << removedOption << std::endl;
        } else {
            std::cout << "Invalid index for option removal." << std::endl;
        }
    }

    void displayMenu() {
        if (options.empty()) {
            std::cout << "Menu is empty." << std::endl;
        } else {
            std::cout << "Menu Options:" << std::endl;
            for (size_t i = 0; i < options.size(); ++i) {
                std::cout << i << ". " << options[i] << std::endl;
            }
        }
    }

    void selectOption(int index) {
        if (index >= 0 && index < options.size()) {
            std::cout << "Selected option: " << options[index] << std::endl;
        } else {
            std::cout << "Invalid index for option selection." << std::endl;
        }
    }
};

int main() {
    Menu menu;

    while (true) {
        std::cout << "\nMenu System:" << std::endl;
        std::cout << "1. Display Menu" << std::endl;
        std::cout << "2. Add Option" << std::endl;
        std::cout << "3. Remove Option" << std::endl;
        std::cout << "4. Select Option" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                menu.displayMenu();
                break;
            case 2:
                std::cout << "Enter option to add: ";
                std::string option;
                std::cin >> option;
                menu.addOption(option);
                break;
            case 3:
                std::cout << "Enter index of option to remove: ";
                std::cin >> option;
                menu.removeOption(option);
                break;
            case 4:
                std::cout << "Enter index of option to select: ";
                std::cin >> option;
                menu.selectOption(option);
                break;
            case 5:
                std::cout << "Exiting menu system." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
