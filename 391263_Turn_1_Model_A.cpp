#include <iostream>
#include <string>

// Example function that might fail
bool performOperation(int input) {
    if (input < 0) {
        return false; // Simulate an error
    }
    return true;
}

// Function to display feedback
void displayFeedback(const std::string& message) {
    std::cout << "Feedback: " << message << std::endl;
}

// Function to handle user input
int getUserInput() {
    int input;
    std::cout << "Enter an integer: ";
    while (!(std::cin >> input)) {
        std::cin.clear(); // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Invalid input. Please enter a valid integer: ";
    }
    return input;
}

int main() {
    while (true) {
        int userInput = getUserInput();
        
        if (performOperation(userInput)) {
            displayFeedback("Operation successful!");
        } else {
            displayFeedback("Operation failed. Please try again.");
        }

        // Option to exit the loop
        char continueOption;
        std::cout << "Do you want to continue? (y/n): ";
        std::cin >> continueOption;
        if (continueOption != 'y') {
            break;
        }
    }

    return 0;
}
