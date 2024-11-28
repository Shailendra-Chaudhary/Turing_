#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

// Function to load an image from a file
std::vector<Pixel> loadImage(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return {};
    }

    std::vector<Pixel> image(IMAGE_WIDTH * IMAGE_HEIGHT);
    file.read((char*)&image[0], sizeof(Pixel) * image.size());
    if (file.gcount() != sizeof(Pixel) * image.size()) {
        std::cerr << "Error: Could not read the entire file '" << filename << "'" << std::endl;
        return {};
    }

    file.close();
    return image;
}

// Function to save an image to a file
void saveImage(const std::string& filename, const std::vector<Pixel>& image) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return;
    }

    file.write((char*)&image[0], sizeof(Pixel) * image.size());
    file.close();
}

// Function to convert an image to grayscale
std::vector<Pixel> convertToGrayscale(const std::vector<Pixel>& image) {
    std::vector<Pixel> grayscaleImage(image);

    for (size_t i = 0; i < grayscaleImage.size(); ++i) {
        unsigned char grayscaleValue = (grayscaleImage[i].red + grayscaleImage[i].green + grayscaleImage[i].blue) / 3;
        grayscaleImage[i].red = grayscaleImage[i].green = grayscaleImage[i].blue = grayscaleValue;
    }

    return grayscaleImage;
}

// Function to apply the Sobel operator for edge detection
std::vector<Pixel> applySobelOperator(const std::vector<Pixel>& image) {
    const int sobelX[] = { -1, 0, 1,
                           -2, 0, 2,
                           -1, 0, 1 };

    const int sobelY[] = { -1, -2, -1,
                           0,  0,  0,
                           1,  2,  1 };

    std::vector<Pixel> resultImage(image);

    for (size_t y = 1; y < IMAGE_HEIGHT - 1; ++y) {
        for (size_t x = 1; x < IMAGE_WIDTH - 1; ++x) {
            int gx = 0, gy = 0;
            for (int ky = 0; ky < 3; ++ky) {
                for (int kx = 0; kx < 3; ++kx) {
                    int i = y + ky - 1;
                    int j = x + kx - 1;
                    gx += sobelX[ky * 3 + kx] * image[i * IMAGE_WIDTH + j].red;
                    gy += sobelY[ky * 3 + kx] * image[i * IMAGE_WIDTH + j].red;
                }
            }

            int gradientMagnitude = static_cast<int>(std::sqrt(gx * gx + gy * gy));
            resultImage[y * IMAGE_WIDTH + x].red = resultImage[y * IMAGE_WIDTH + x].green = resultImage[y * IMAGE_WIDTH + x].blue = 255 - gradientMagnitude;
        }
    }

    return resultImage;
}

int main() {
    std::string inputFile = "input.bmp";
    std::string outputFile = "output_edges.bmp";

    // Load the input image
    std::vector<Pixel> image = loadImage(inputFile);
    if (image.empty()) {
        return 1;
    }

    // Convert the image to grayscale
    std::vector<Pixel> grayscaleImage = convertToGrayscale(image);

    // Apply the Sobel operator for edge detection
    std::vector<Pixel> edgeImage = applySobelOperator(grayscaleImage);

    // Save the edge-detected image
    saveImage(outputFile, edgeImage);

    std::cout << "Edge detection complete. Image saved to '" << outputFile << "'" << std::endl;
    return 0;
}
