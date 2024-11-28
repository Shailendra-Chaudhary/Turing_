
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <functional>

// Image data structure using a typedef to improve readability
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Pixel;

// Constants for image dimensions
constexpr int IMAGE_WIDTH = 640;
constexpr int IMAGE_HEIGHT = 480;
constexpr size_t IMAGE_SIZE = IMAGE_WIDTH * IMAGE_HEIGHT;

// Function prototype to load image data from a file
std::vector<Pixel> loadImageFromFile(const std::string& filename);

// Function prototype to save image data to a file
void saveImageToFile(const std::string& filename, const std::vector<Pixel>& image);

// Function prototype to convert an image to grayscale
std::vector<Pixel> convertToGrayscale(const std::vector<Pixel>& image);

// Function to validate image size before processing
void validateImageSize(const std::vector<Pixel>& image) {
    if (image.size() != IMAGE_SIZE) {
        throw std::runtime_error("Invalid image size: Expected " + std::to_string(IMAGE_SIZE) + " pixels.");
    }
}

int main() {
    std::string inputFile = "input.bmp";
    std::string outputFile = "output_grayscale.bmp";
    
    try {
        // Load the input image
        std::vector<Pixel> image = loadImageFromFile(inputFile);
        
        // Validate the image size before processing
        validateImageSize(image);
        
        // Apply image processing algorithm
        std::vector<Pixel> grayscaleImage = convertToGrayscale(image);
        
        // Save the grayscale image
        saveImageToFile(outputFile, grayscaleImage);
        
        std::cout << "Grayscale conversion complete. Image saved to: " << outputFile << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
 
// Revised function to load image data from a file
std::vector<Pixel> loadImageFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file '" + filename + "'");
    }
    std::vector<Pixel> image(IMAGE_SIZE);

    file.read(reinterpret_cast<char*>(image.data()), sizeof(Pixel) * image.size());
    if (!file) {
        throw std::runtime_error("Error reading file '" + filename + "'");
    }

    file.close();
    return image;
}

// Revised function to save image data to a file
void saveImageToFile(const std::string& filename, const std::vector<Pixel>& image) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file '" + filename + "'");
    }

    file.write(reinterpret_cast<const char*>(image.data()), sizeof(Pixel) * image.size());
    if (!file) {
        throw std::runtime_error("Error writing to file '" + filename + "'");        
    }
    file.close();
}

// Revised function to perform grayscale conversion
std::vector<Pixel> convertToGrayscale(const std::vector<Pixel>& image) {
    std::vector<Pixel> grayscaleImage(image);
    // ... Grayscale conversion logic stays the same ...
    return grayscaleImage;
} 
                    
