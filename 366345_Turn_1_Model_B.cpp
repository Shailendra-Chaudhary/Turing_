#include <iostream>
#include <string>
#include <unordered_map>

enum class ErrorCode {
    SUCCESS = 0,
    INVALID_INPUT = 1,
    FILE_NOT_FOUND = 2,
    INTERNAL_ERROR = 3,
    // Add more error codes as needed
};

class Error {
public:
    Error(ErrorCode code, const std::string& message) : code_(code), message_(message) {}

    ErrorCode code() const { return code_; }
    const std::string& message() const { return message_; }

private:
    ErrorCode code_;
    std::string message_;
};

class ErrorManager {
public:
    static const ErrorManager& instance() {
        static ErrorManager manager;
        return manager;
    }

    const std::string& getErrorMessage(ErrorCode code) const {
        auto it = errorMessages_.find(code);
        if (it != errorMessages_.end()) {
            return it->second;
        }
        return defaultErrorMessage_;
    }

    void addErrorMessage(ErrorCode code, const std::string& message) {
        errorMessages_[code] = message;
    }

private:
    ErrorManager() {
        // Initialize default error messages for common error codes
        addErrorMessage(ErrorCode::SUCCESS, "Operation succeeded");
        addErrorMessage(ErrorCode::INVALID_INPUT, "Invalid input provided");
        addErrorMessage(ErrorCode::FILE_NOT_FOUND, "File not found");
        addErrorMessage(ErrorCode::INTERNAL_ERROR, "Internal error occurred");
    }

    std::unordered_map<ErrorCode, std::string> errorMessages_;
    const std::string defaultErrorMessage_ = "Unknown error";
};

// Function that can throw an Error
void someFunctionThatThrowsError(const std::string& input) {
    if (input.empty()) {
        throw Error(ErrorCode::INVALID_INPUT, "Input cannot be empty");
    }
    // Add more error handling logic as needed
}

int main() {
    try {
        std::string input;
        std::cout << "Enter input: ";
        std::getline(std::cin, input);

        someFunctionThatThrowsError(input);

        std::cout << "Success!" << std::endl;
    } catch (const Error& e) {
        std::cout << "Error: " << ErrorManager::instance().getErrorMessage(e.code()) << " (" << static_cast<int>(e.code()) << ")" << std::endl;
    }

    return 0;
}  
