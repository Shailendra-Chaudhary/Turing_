#include <iostream>
#include <string>

// Enum for error codes
enum class ErrorCode : int {
    Success = 0,
    FileNotFound = 1,
    InvalidInput = 2,
    OutOfMemory = 3,
    UnknownError = 999
};

// Function to convert ErrorCode enum to a string
std::string ErrorCodeToString(ErrorCode code) {
    switch (code) {
        case ErrorCode::Success:
            return "Success";
        case ErrorCode::FileNotFound:
            return "File not found";
        case ErrorCode::InvalidInput:
            return "Invalid input";
        case ErrorCode::OutOfMemory:
            return "Out of memory";
        case ErrorCode::UnknownError:
            return "Unknown error";
        default:
            return "Unknown error code";
    }
}

// Function that demonstrates error handling using the ErrorCode enum
ErrorCode someFunction(const std::string& filename) {
    // Simulate a file not found error
    if (filename == "non_existent_file.txt") {
        return ErrorCode::FileNotFound;
    }

    // Simulate an invalid input error
    if (filename.empty()) {
        return ErrorCode::InvalidInput;
    }

    // Simulate successful execution
    return ErrorCode::Success;
}

int main() {
    std::string filename = "non_existent_file.txt"; // Change this to "valid_file.txt" to see a different error
    ErrorCode result = someFunction(filename);

    // Check the result and display a message
    if (result != ErrorCode::Success) {
        std::cerr << "An error occurred: " << ErrorCodeToString(result) << std::endl;
    } else {
        std::cout << "Operation successful." << std::endl;
    }

    return 0;
}
