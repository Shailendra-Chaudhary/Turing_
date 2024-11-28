
#include <iostream>
#include <fftw3.h>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

// Function to load an image from a file
bool loadImage(const std::string& filename, std::vector<float>& imageData, int& width, int& height) {
    // Open the file
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    // Read the header information
    char header[54];
    file.read(header, 54);
    if (std::memcmp(header, "BM", 2) != 0) {
        std::cerr << "Invalid BMP file format." << std::endl;
        return false;
    }
    // Extract image width and height from the header
    width = *(int*)(header + 18);
    height = *(int*)(header + 22);
    int pixelSize = *(int*)(header + 28) / 8; // Number of bytes per pixel
    if (pixelSize != 1) {
        std::cerr << "Only grayscale images are supported for now." << std::endl;
        return false;
    }
    // Calculate the image size
    size_t imageSize = width * height;
    // Allocate memory for the image data
    imageData.resize(imageSize);
    // Read the image data
    file.read((char*)imageData.data(), imageSize);
    // Close the file
    file.close();
    return true;
}
 
// Function to compress the image using FFT
void compressImage(const std::vector<float>& inputImage, std::vector<float>& compressedData, int width, int height) {
    int imageSize = width * height;
    // Allocate memory for the FFT input and output
    fftwf_complex* input = (fftwf_complex*)fftwf_malloc(imageSize * sizeof(fftwf_complex));
    fftwf_complex* output = (fftwf_complex*)fftwf_malloc(imageSize * sizeof(fftwf_complex));
    // Create a 2D FFT plan
    fftwf_plan plan = fftwf_plan_dft_2d(height, width, input, output, FFTW_FORWARD, FFTW_MEASURE);
    // Copy the input image data to the FFT input
    for (int i = 0; i < imageSize; i++) {
        input[i][0] = inputImage[i];
        input[i][1] = 0.0;
    }
    // Perform the FFT
    fftwf_execute(plan);
    // Save the compressed data (real part only)
    compressedData.resize(imageSize);
    for (int i = 0; i < imageSize; i++) {
        compressedData[i] = output[i][0];
    }
    // Destroy the FFT plan
    fftwf_destroy_plan(plan);
    // Free the FFT input and output memory
    fftwf_free(input);
    fftwf_free(output);
}
 
// Function to decompress the image using FFT
void decompressImage(const std::vector<float>& compressedData, std::vector<float>& decompressedData, int width, int height) {
    int imageSize = width * height;
    // Allocate memory for the FFT input and output
    fftwf_complex* input = (fftwf_complex*)fftwf_malloc(imageSize * sizeof(fftwf_complex));
    fftwf_complex* output = (fftwf_complex*)fftwf_malloc(imageSize * sizeof(fftwf_complex));
