      #include <iostream>
      #include <fstream>
      #include <string>
      #include <exception>
      #include <vector>
      #include <sstream>
      #include <filesystem>

      namespace fs = std::filesystem;

      const std::string DATA_DIR_PATH = "./persistent_data";
      const std::string SETTINGS_FILE_PATH = DATA_DIR_PATH + "/settings.txt";
      const std::string TEMP_DATA_FILE_PATH = DATA_DIR_PATH + "/temp_data.txt";

      // Struct to hold settings data
      struct Settings {
          std::string temperatureSensorCalibration;
          std::string humiditySensorCalibration;
      };

      // Function to save settings to persistent memory
      void saveSettings(const Settings& settings) {
          try {
              std::ofstream file(SETTINGS_FILE_PATH);
              if (!file.is_open()) {
                  throw std::runtime_error("Failed to open settings file for writing.");
              }
              file << settings.temperatureSensorCalibration << "\n"
                   << settings.humiditySensorCalibration;
              file.close();
              std::cout << "Settings saved successfully." << std::endl;
          } catch (const std::exception& e) {
              std::cerr << "Error saving settings: " << e.what() << std::endl;
          }
      }

      // Function to load settings from persistent memory
      Settings loadSettings() {
          Settings settings;
          try {
              std::ifstream file(SETTINGS_FILE_PATH);
              if (!file.is_open()) {
                  std::cout << "Settings file not found. Creating a new one." << std::endl;
                  // Default settings if file not found
                  settings.temperatureSensorCalibration = "25.0";
                  settings.humiditySensorCalibration = "60.0";
                  saveSettings(settings);
                  return settings;
              }
              std::getline(file, settings.temperatureSensorCalibration);
              std::getline(file, settings.humiditySensorCalibration);
              file.close();
              return settings;
          } catch (const std::exception& e) {
              std::cerr << "Error loading settings: " << e.what() << std::endl;
              // Default settings on error
              settings.temperatureSensorCalibration = "25.0";
              settings.humiditySensorCalibration = "60.0";
              return settings;
          }
      }

      // Function to append temp readings to persistent memory (append mode)
      void saveTemperatureReadings(const std::vector<double>& readings) {
          try {
              std::ofstream file(TEMP_DATA_FILE_PATH, std::ios::app);
              if (!file.is_open()) {
                  throw std::runtime_error("Failed to open temperature file for writing.");
              }
              for (const double& reading : readings) {
                  file << reading << "\n";
              }
              file.close();
              std::cout << "Temperature readings saved successfully." << std::endl;
          } catch (const std::exception& e) {
              std::cerr << "Error saving temperature readings: " << e.what() << std::endl;
          }
      }

      // Function to load all temperature readings from persistent memory
      std::vector<double> loadTemperatureReadings() {
          std::vector<double> readings;
          try {
              std::ifstream file(TEMP_DATA_FILE_PATH);
              if (!file.is_open()) {
                  return readings;
              }
              std::string line;
              while (std::getline(file, line)) {
                  double reading;
                  if (std::istringstream(line) >> reading) {
                      readings.push_back(reading);
                  } else {
                      std::cerr << "Invalid temperature reading format found: " << line << std::endl;
                  }
              }
              file.close();
              return readings;
