#include <iostream>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <string_view>

// Define an enum class for error codes
enum class ErrorCode : int {
    SUCCESS = 0,
    INVALID_INPUT = 101,
    FILE_NOT_FOUND = 102,
    INTERNAL_ERROR = 103,
    NETWORK_ERROR = 104,
    // Add more error codes as needed
};

// Define a class to wrap an ErrorCode and optional message
class Error {
public:
    Error(ErrorCode code, const std::string_view& message = "")
        : code_(code), message_(message) {}

    ErrorCode code() const { return code_; }
    std::string_view message() const { return message_; }

private:
    ErrorCode code_;
    std::string_view message_;
};

// Singleton ErrorMessageManager to store and retrieve error messages
class ErrorMessageManager {
public:
    static ErrorMessageManager& instance() {
        static ErrorMessageManager instance_;
        return instance_;
    }

    const std::string& getMessage(ErrorCode code) const {
        auto it = errorMessages_.find(code);
        return it != errorMessages_.end() ? it->second : defaultMessage_;
    }

    void addMessage(ErrorCode code, const std::string& message) {
        errorMessages_[code] = message;
    }

private:
    ErrorMessageManager() {
        // Initialize default error messages for common error codes
        addMessage(ErrorCode::SUCCESS, "Operation completed successfully.");
        addMessage(ErrorCode::INVALID_INPUT, "Invalid input provided.");
        addMessage(ErrorCode::FILE_NOT_FOUND, "File not found.");
        addMessage(ErrorCode::INTERNAL_ERROR, "An internal error occurred.");
        addMessage(ErrorCode::NETWORK_ERROR, "A network error occurred.");
    }

    std::unordered_map<ErrorCode, std::string> errorMessages_;
    const std::string defaultMessage_ = "Unknown error occurred.";
};

// Define a function that throws an Error
void someFunction(const std::string& inputFile) {
    if (inputFile.empty()) {
        throw Error(ErrorCode::INVALID_INPUT, "Input file name cannot be empty.");
    }

    try {
        // Simulate a file operation that might throw an error
        std::string fileContent;
        // Replace this with actual file-reading logic
        throw std::runtime_error("File read failed."); // Throws an error
    } catch (const std::exception& e) {
        throw Error(ErrorCode::INTERNAL_ERROR, fmt::format("Internal error: {}", e.what()));
    }
}

int main() {
    try {
        std::string inputFileName;
        std::cout << "Enter file name: ";
        std::cin >> inputFileName;

        someFunction(inputFileName);

        std::cout << "Processing successful." << std::endl;
    } catch (const Error& e) {
        std::cout << "Error: " << ErrorMessageManager::instance().getMessage(e.code()) << " (" << e.code() << ")" << std::endl;
        if (!e.message().empty()) {
            std::cout << "Details: " << e.message() << std::endl;
        }
    }

    return 0;
}
