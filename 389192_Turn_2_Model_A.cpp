#include <iostream>
#include <fftw3.h>
#include <vector>
#include <fstream>

// Load a BMP grayscale image into a 1D vector
bool loadImage(const std::string& filename, std::vector<float>& imageData, int& width, int& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    char header[54];
    file.read(header, 54);
    if (std::memcmp(header, "BM", 2) != 0) {
        std::cerr << "Invalid BMP file format." << std::endl;
        return false;
    }

    width = *(int*)(header + 18);
    height = *(int*)(header + 22);
    int pixelSize = *(int*)(header + 28) / 8;
    if (pixelSize != 1) {
        std::cerr << "Only grayscale images are supported for now." << std::endl;
        return false;
    }

    size_t imageSize = width * height;
    imageData.resize(imageSize);
    file.read((char*)imageData.data(), imageSize);
    file.close();

    return true;
}

// Perform FFT on the image data
void fftCompress(const std::vector<float>& inputData, std::vector<float>& fftData, int width, int height) {
    int imageSize = width * height;
    fftwf_complex* input = (fftwf_complex*)fftwf_malloc(imageSize * sizeof(fftwf_complex));
    fftwf_complex* output = (fftwf_complex*)fftwf_malloc(imageSize * sizeof(fftwf_complex));

    fftwf_plan plan = fftwf_plan_dft_2d(height, width, input, output, FFTW_FORWARD, FFTW_MEASURE);

    // Prepare input data
    for (int i = 0; i < imageSize; ++i) {
        input[i][0] = inputData[i];
        input[i][1] = 0.0f;
    }

    // Execute FFT
    fftwf_execute(plan);

    // Save FFT output (magnitude or real part for basic compression)
    fftData.resize(imageSize);
    for (int i = 0; i < imageSize; ++i) {
        fftData[i] = std::sqrt(input[i][0] * input[i][0] + input[i][1] * input[i][1]);
    }

    fftwf_destroy_plan(plan);
    fftwf_free(input);
    fftwf_free(output);
}

// Perform IFFT to decompress the image data
void fftDecompress(const std::vector<float>& fftData, std::vector<float>& decompressedData, int width, int height) {
    int imageSize = width * height;
    fftwf_complex* input = (fftwf_complex*)fftwf_malloc(imageSize * sizeof(fftwf_complex));
    fftwf_complex* output = (fftwf_complex*)fftwf_malloc(imageSize * sizeof(fftwf_complex));

    fftwf_plan plan = fftwf_plan_dft_2d(height, width, input, output, FFTW_BACKWARD, FFTW_MEASURE);

    // Prepare input data (using magnitude or real part)
    for (int i = 0; i < imageSize; ++i) {
        input[i][0] = fftData[i];
        input[i][1] = 0.0f;
    }

    // Execute IFFT
    fftwf_execute(plan);
    for (int i = 0; i < imageSize; ++i) {
        input[i][0] /= (float)width * height;
    }

    // Save decompressed data
    decompressedData.resize(imageSize);
    for (int i = 0; i < imageSize; ++i) {
        decompressedData[i] = input[i][0];
    }

    fftwf_destroy_plan(plan);
    fftwf_free(input);
    fftwf_free(output);
}

int main() {
    int width, height;
    std::string inputFile = "input.bmp";

    std::vector<float> imageData;
    if (!loadImage(inputFile, imageData, width, height)) {
        return 1;
    }

    std::vector<float> fftData;
    fftCompress(imageData, fftData, width, height);

    std::vector<float> decompressedData;
    fftDecompress(fftData, decompressedData, width, height);

    // Save the decompressed image to a file (not shown here)

    return 0;
}
