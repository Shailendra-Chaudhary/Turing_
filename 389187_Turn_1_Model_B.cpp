#include <cmath>
#include <iostream>
using namespace std;

//Function to perform Gaussian Blur
void gaussianBlur(float** image, int height, int width, float sigma)
{
    //Kernel size is calculated based on the sigma value
    const int kernelSize = static_cast<int>(2.0 * ceil(3.0 * sigma) + 1.0);

    //Initialize the Gaussian kernel
    float kernel[kernelSize];
    float sum = 0.0f;
    for (int i = 0; i < kernelSize; ++i) {
        const float x = static_cast<float>(i - kernelSize / 2);
        kernel[i] = expf(-0.5f * x * x / (sigma * sigma)) / (sigma * sqrt(2 * M_PI));
        sum += kernel[i];
    }
    
    //Normalize the kernel
    for (int i = 0; i < kernelSize; ++i) {
        kernel[i] /= sum;
    }

    //Create a temporary image to store the blurred result
    float** blurredImage = new float*[height];
    for (int i = 0; i < height; ++i) {
        blurredImage[i] = new float[width];
    }

    // Perform the Gaussian blur using the separable kernel
    for (int i = 0; i < height; ++i) {
        // Blur along the x-axis
        for (int j = 0; j < width; ++j) {
            float blurValue = 0.0f;
            for (int k = -kernelSize / 2; k <= kernelSize / 2; ++k) {
                const int x = j + k;
                // Handle boundary conditions
                if (x >= 0 && x < width) {
                    blurValue += image[i][x] * kernel[k + kernelSize / 2];
                }
            }
            blurredImage[i][j] = blurValue;
        }
    }
 
    // Transpose the image for blurring along the y-axis
    float** transposedImage = new float*[width];
    for (int i = 0; i < width; ++i) {
        transposedImage[i] = new float[height];
        for (int j = 0; j < height; ++j) {
            transposedImage[i][j] = blurredImage[j][i];
        }
    }

    // Blur along the y-axis using the same kernel
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            float blurValue = 0.0f;
            for (int k = -kernelSize / 2; k <= kernelSize / 2; ++k) {
                const int y = j + k;
                if (y >= 0 && y < height) {
                    blurValue += transposedImage[i][y] * kernel[k + kernelSize / 2];
                }
            }
            image[j][i] = blurValue;
        }
    }

    //Free the temporary image memory
    for (int i = 0; i < height; ++i) {
        delete[] blurredImage[i];
    }
    delete[] blurredImage;

    for (int i = 0; i < width; ++i) {
        delete[] transposedImage[i];
    }
    delete[] transposedImage;
}
