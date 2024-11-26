#include <iostream>
#include <string>
#include <unordered_map>

namespace ErrorCode {
    enum class Code {
        SUCCESS = 0,
        INVALID_INPUT = 1,
        FILE_NOT_FOUND = 2,
        INTERNAL_ERROR = 3,
        INSUFFICIENT_FUNDS = 4,
        // Add more error codes as needed for each subsystem
        SUBSYSTEM_A_ERROR_1 = 100,
        SUBSYSTEM_B_ERROR_2 = 200,
        // Continue this pattern for subsystems
    };

    constexpr auto SUCCESS = static_cast<int>(Code::SUCCESS);
    constexpr auto INVALID_INPUT = static_cast<int>(Code::INVALID_INPUT);
    constexpr auto FILE_NOT_FOUND = static_cast<int>(Code::FILE_NOT_FOUND);
    // Add more constexpr for common error codes

    class Error {
    public:
        Error(Code code, const std::string& message) : code_(code), message_(message) {}

        Code code() const { return code_; }
        const std::string& message() const { return message_; }

    private:
        Code code_;
        std::string message_;
    };

    class Manager {
    public:
        static const Manager& instance() {
            static Manager manager;
            return manager;
        }

        const std::string& getMessage(Code code) const {
            auto it = errorMessages_.find(code);
            if (it != errorMessages_.end()) {
                return it->second;
            }
            return defaultMessage_;
        }

        void addMessage(Code code, const std::string& message) {
            errorMessages_[code] = message;
        }

    private:
        Manager() {
            // Initialize default error messages
            addMessage(Code::SUCCESS, "Operation succeeded");
            addMessage(Code::INVALID_INPUT, "Invalid input provided");
            addMessage(Code::FILE_NOT_FOUND, "File not found");
            // Add default messages for other common codes

            // Add messages for specific subsystems
            addMessage(Code::SUBSYSTEM_A_ERROR_1, "Subsystem A error 1 occurred");
            addMessage(Code::SUBSYSTEM_B_ERROR_2, "Subsystem B error 2 occurred");
        }

        std::unordered_map<Code, std::string> errorMessages_;
        const std::string defaultMessage_ = "Unknown error";
    };
}  // namespace ErrorCode

// Functions that can throw errors
void someFunction(const std::string& input) {
    if (input.empty()) {
        throw ErrorCode::Error(ErrorCode::INVALID_INPUT, "Input cannot be empty");
    }
    // Add more error handling logic
}

void someOtherFunction() {
    // Use ErrorCode::Code::SUBSYSTEM_A_ERROR_1 for subsystem-specific errors
    if (someConditionNotMet()) {
        throw ErrorCode::Error(ErrorCode::Code::SUBSYSTEM_A_ERROR_1, "Something went wrong in subsystem A");
    }
}

int main() {
    try {
        std::string input;
        std::cout << "Enter input: ";
        std::getline(std::cin, input);

        someFunction(input);
        someOtherFunction();

        std::cout << "Success!" << std::endl;
    } catch (const ErrorCode::Error& e) {
        std::cout << "Error: " << ErrorCode::Manager::instance().getMessage(e.code()) << " (" << static_cast<int>(e.code()) << ")" << std::endl;
    }

    return 0;
}
