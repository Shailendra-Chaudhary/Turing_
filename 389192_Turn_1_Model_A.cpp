#include <iostream>
#include <vector>
#include <complex>

using namespace std;

// Function to perform 1D FFT
vector<complex<double>> fft1d(const vector<double>& data) {
    int n = data.size();
    vector<complex<double>> result(n);
    
    for (int k = 0; k < n; ++k) {
        complex<double> sum(0, 0);
        for (int j = 0; j < n; ++j) {
            double angle = -2 * M_PI * j * k / n;
            complex<double> w(cos(angle), sin(angle));
            sum += data[j] * w;
        }
        result[k] = sum;
    }
    return result;
}

// Function to perform 2D FFT
vector<vector<complex<double>>> fft2d(const vector<vector<double>>& image) {
    vector<vector<complex<double>>> fftImage(image.size(), vector<complex<double>>(image[0].size()));
    
    for (int i = 0; i < image.size(); ++i) {
        fftImage[i] = fft1d(image[i]);
    }
    
    for (int j = 0; j < image[0].size(); ++j) {
        vector<double> column;
        for (int i = 0; i < image.size(); ++i) {
            column.push_back(fftImage[i][j].real());
        }
        fftImage[0][j] = fft1d(column)[0];
        for (int i = 1; i < image.size(); ++i) {
            fftImage[i][j] = fft1d(column)[i];
        }
    }
    
    return fftImage;
}

// Function to perform 2D Inverse FFT
vector<vector<double>> ifft2d(const vector<vector<complex<double>>>& fftImage) {
    vector<vector<double>> image(fftImage.size(), vector<double>(fftImage[0].size()));
    
    for (int i = 0; i < fftImage.size(); ++i) {
        image[i] = ifft1d(fftImage[i]);
    }
    
    for (int j = 0; j < fftImage[0].size(); ++j) {
        vector<complex<double>> column;
        for (int i = 0; i < fftImage.size(); ++i) {
            column.push_back(fftImage[i][j]);
        }
        vector<complex<double>> ifftColumn = ifft1d(column);
        for (int i = 0; i < image.size(); ++i) {
            image[i][j] = ifftColumn[i].real() / fftImage.size();
        }
    }
    
    return image;
}

// Function to perform 1D Inverse FFT
vector<complex<double>> ifft1d(const vector<complex<double>>& data) {
    int n = data.size();
    vector<complex<double>> result(n);
    
    for (int k = 0; k < n; ++k) {
        complex<double> sum(0, 0);
        for (int j = 0; j < n; ++j) {
            double angle = 2 * M_PI * j * k / n;
            complex<double> w(cos(angle), -sin(angle));
            sum += data[j] * w;
        }
        result[k] = sum / n;
    }
    return result;
}

// Function to read an image as a grayscale vector
vector<vector<double>> readImage(const string& filename) {
    // Replace this with actual image reading logic (e.g., using OpenCV)
    return {{1.0, 0.5, 0.0},
            {0.0, 1.0, 0.5},
            {0.5, 0.0, 1.0}};
}

// Function to write an image back from a grayscale vector
void writeImage(const vector<vector<double>>& image, const string& filename) {
    // Replace this with actual image writing logic (e.g., using OpenCV)
}

int main() {
    string imageFilename = "input.png";
    string compressedFilename = "compressed.bin";
    string decompressedFilename = "output.png";
    
    // Read the image
    vector<vector<double>> image = readImage(imageFilename);
    
    // Perform 2D FFT
    vector<vector<complex<double>>> fftImage = fft2d(image);
    
    // Compress the image (e.g., thresholding, quantizing the FFT coefficients)
    for (int i = 0; i < fftImage.size(); ++i) {
        for (int j = 0; j < fftImage[0].size(); ++j) {
            // Threshold the coefficients
            double absValue = abs(fftImage[i][j]);
            if (absValue < 0.5) {
                fftImage[i][j] = complex<double>(0, 0);
            }
        }
    }
    
    // Save the compressed FFT coefficients to a file
    ofstream compressedFile(compressedFilename, ios::binary);
    for (int i = 0; i < fftImage.size(); ++i) {
        for (int j = 0; j < fftImage[0].size(); ++j) {
            compressedFile.write(reinterpret_cast<const char*>(&fftImage[i][j]), sizeof(complex<double>));
        }
    }
    compressedFile.close();
    
    // Load the compressed FFT coefficients from a file
    ifstream compressedFile(compressedFilename, ios::binary);
    vector<vector<complex<double>>> loadedFftImage(fftImage.size(), vector<complex<double>>(fftImage[0].size()));
    for (int i = 0; i < fftImage.size(); ++i) {
        for (int j = 0; j < fftImage[0].size(); ++j) {
            compressedFile.read(reinterpret_cast<char*>(&loadedFftImage[i][j]), sizeof(complex<double>));
        }
    }
    compressedFile.close();
    
    // Perform 2D Inverse FFT
    vector<vector<double>> decompressedImage = ifft2d(loadedFftImage);
    
    // Write the decompressed image
    writeImage(decompressedImage, decompressedFilename);
    
    return 0;
}
