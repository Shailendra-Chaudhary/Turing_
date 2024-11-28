
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include "kiss_fft.h"

// Function to load an image from a file
bool loadImage(const std::string& filename, std::vector<float>& imageData, int& width, int& height) {
    // ... (Same code as before)
}
 
// Function to compress the image using FFT
void compressImage(const std::vector<float>& inputImage, std::vector<float>& compressedData, int width, int height) {
    int imageSize = width * height;

    // Calculate the number of FFT bins
    int nBins = width * height;
    
    // Allocate memory for the FFT input and output
    kiss_fft_cpx* input = (kiss_fft_cpx*)kiss_fft_alloc(nBins, 0, NULL, NULL);
    kiss_fft_cpx* output = (kiss_fft_cpx*)kiss_fft_alloc(nBins, 0, NULL, NULL);
    
    // Create a 2D FFT plan
    kiss_fft_cfg fft_cfg = kiss_fft_alloc(nBins, 0, NULL, NULL);

    // Copy the input image data to the FFT input
    for (int i = 0; i < imageSize; i++) {
        input[i].r = inputImage[i];
        input[i].i = 0.0;
    }

    // Perform the FFT
    kiss_fft(fft_cfg, input, output);

    // Save the compressed data (real part only)
    compressedData.resize(nBins);
    for (int i = 0; i < nBins; i++) {
        compressedData[i] = output[i].r;
    }

    // Destroy the FFT plan
    kiss_fft_free(fft_cfg);
    // Free the FFT input and output memory
    free(input);
    free(output);
}
 
// Function to decompress the image using FFT
void decompressImage(const std::vector<float>& compressedData, std::vector<float>& decompressedData, int width, int height) {
    int imageSize = width * height;

    // Calculate the number of FFT bins
    int nBins = width * height;

    // Allocate memory for the FFT input and output
    kiss_fft_cpx* input = (kiss_fft_cpx*)kiss_fft_alloc(nBins, 1, NULL, NULL);
    kiss_fft_cpx* output = (kiss_fft_cpx*)kiss_fft_alloc(nBins, 1, NULL, NULL);

    // Create a 2D FFT plan
    kiss_fft_cfg fft_cfg = kiss_fft_alloc(nBins, 1, NULL, NULL);

    // Copy the compressed data (real part only) to the FFT input
    for (int i = 0; i < nBins; i++) {
        input[i].r = compressedData[i];
        input[i].i = 0.0;
    }

    // Perform the Inverse FFT
    kiss_fft(fft_cfg, input, output);

    // Save the decompressed data
    decompressedData.resize(imageSize);
    for (int i = 0; i < imageSize; i++) {
        decompressedData[i] = output[i].r / (float)nBins; // Normalize by the number of bins
    }

    // Destroy the FFT plan
    kiss_fft_free(fft_cfg);
    // Free the FFT input and output memory
    free(input);
    free(output);
}
 
 int main() {
    const std::string inputImageFilename = "input_image.bmp";
    const std::string compressedImageFilename = "compressed_image.bin";
