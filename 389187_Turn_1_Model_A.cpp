#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

std::vector<Pixel> loadImage(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return std::vector<Pixel>();
    }

    std::vector<Pixel> image(IMAGE_WIDTH * IMAGE_HEIGHT);

    file.read((char*)&image[0], sizeof(Pixel) * image.size());
    if (file.gcount() != sizeof(Pixel) * image.size()) {
        std::cerr << "Error: Could not read the entire file '" << filename << "'" << std::endl;
        return std::vector<Pixel>();
    }

    file.close();
    return image;
}

void saveImage(const std::string& filename, const std::vector<Pixel>& image) {
    std::ofstream file(filename, std::ios::binary | std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return;
    }

    file.write((char*)&image[0], sizeof(Pixel) * image.size());
    file.close();
}

std::vector<Pixel> convertToGrayscale(const std::vector<Pixel>& image) {
    std::vector<Pixel> grayscaleImage(image);

    for (size_t i = 0; i < grayscaleImage.size(); ++i) {
        // Calculate the grayscale value using the average of R, G, and B
        unsigned char grayscaleValue = (grayscaleImage[i].red + grayscaleImage[i].green + grayscaleImage[i].blue) / 3;

        // Assign the grayscale value to all three RGB components
        grayscaleImage[i].red = grayscaleImage[i].green = grayscaleImage[i].blue = grayscaleValue;
    }

    return grayscaleImage;
}

int main() {
    std::string inputFile = "input.bmp";
    std::string outputFile = "output_grayscale.bmp";

    // Load the input image
    std::vector<Pixel> image = loadImage(inputFile);
    if (image.empty()) {
        return 1;
    }

    // Convert the image to grayscale
    std::vector<Pixel> grayscaleImage = convertToGrayscale(image);

    // Save the grayscale image
    saveImage(outputFile, grayscaleImage);

    std::cout << "Grayscale conversion complete. Image saved to '" << outputFile << "'" << std::endl;
    return 0;
}
