#include <iostream>
#include <cmath>
#include <vector>

// Model
class WaveData {
private:
    double frequency = 1.0;
    double amplitude = 1.0;
    std::vector<double> xValues;
    std::vector<double> yValues;

public:
    WaveData() {
        initializeData();
    }

    void setFrequency(double freq) {
        frequency = freq;
        initializeData();
    }

    void setAmplitude(double amp) {
        amplitude = amp;
        initializeData();
    }

    const std::vector<double>& getXValues() const {
        return xValues;
    }

    const std::vector<double>& getYValues() const {
        return yValues;
    }

private:
    void initializeData() {
        xValues.clear();
        yValues.clear();

        for (double x = -10.0; x <= 10.0; x += 0.1) {
            xValues.push_back(x);
            yValues.push_back(amplitude * sin(2 * M_PI * frequency * x));
        }
    }
};

// View
class WaveView {
private:
    WaveData* model;

public:
    WaveView(WaveData* model) : model(model) {}

    void display() const {
        std::cout << "Frequency: " << model->getFrequency() << ", Amplitude: " << model->getAmplitude() << std::endl;
        for (size_t i = 0; i < model->getXValues().size(); ++i) {
            std::cout << model->getXValues()[i] << " " << model->getYValues()[i] << std::endl;
        }
    }
};

// Controller
class WaveController {
private:
    WaveData* model;
    WaveView* view;

public:
    WaveController(WaveData* model, WaveView* view) : model(model), view(view) {}

    void handleInput() {
        std::string input;
        double value;

        while (true) {
            std::cout << "Enter 'f' to set frequency, 'a' to set amplitude, or 'q' to quit: ";
            std::getline(std::cin, input);

            if (input == "q") {
                break;
            } else if (input == "f") {
                std::cout << "Enter frequency: ";
                std::cin >> value;
                model->setFrequency(value);
            } else if (input == "a") {
                std::cout << "Enter amplitude: ";
                std::cin >> value;
                model->setAmplitude(value);
            } else {
                std::cout << "Invalid input, please try again." << std::endl;
            }

            view->display();
        }
    }
};

// Main function
int main() {
    WaveData model;
    WaveView view(&model);
    WaveController controller(&model, &view);

    controller.handleInput();

    return 0;
}
