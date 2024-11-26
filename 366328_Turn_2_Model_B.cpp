#include <iostream>
#include <ftdi.h>

#define SENSOR_VENDOR_ID 0x0403 // Replace with the actual vendor ID of your sensor
#define SENSOR_PRODUCT_ID 0x6001 // Replace with the actual product ID of your sensor

int main() {
    struct ftdi_context *ftdi;
    int ret;

    // Initialize FTDI context
    ftdi = ftdi_new();
    if (!ftdi) {
        std::cout << "Failed to initialize FTDI context." << std::endl;
        return 1;
    }

    // Open the device by its vendor ID and product ID
    ret = ftdi_usb_open(ftdi, SENSOR_VENDOR_ID, SENSOR_PRODUCT_ID);
    if (ret < 0) {
        std::cout << "Failed to open device: " << ftdi_get_error_string(ftdi) << std::endl;
        ftdi_free(ftdi);
        return 1;
    }

    // Reset the device
    ret = ftdi_usb_reset(ftdi);
    if (ret < 0) {
        std::cout << "Failed to reset device: " << ftdi_get_error_string(ftdi) << std::endl;
        ftdi_usb_close(ftdi);
        ftdi_free(ftdi);
        return 1;
    }

    // Set baud rate
    ret = ftdi_set_baudrate(ftdi, 9600);
    if (ret < 0) {
        std::cout << "Failed to set baud rate: " << ftdi_get_error_string(ftdi) << std::endl;
        ftdi_usb_close(ftdi);
        ftdi_free(ftdi);
        return 1;
    }
    // Read data from the sensor
    unsigned char data[1024];
    int bytes_read;
    while (true) {
        ret = ftdi_read_data(ftdi, data, sizeof(data), &bytes_read);
        if (ret < 0) {
            std::cout << "Failed to read data: " << ftdi_get_error_string(ftdi) << std::endl;
