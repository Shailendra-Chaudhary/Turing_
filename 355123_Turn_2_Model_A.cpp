#include <iostream>
#include <cstdint>
#include <cstring>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <error.h>

#define INCLUDE_CPUINFO
#if defined (__i386__) || defined (__x86_64__)
 #include <cpuid.h>
 #elif defined (__aarch64__)
 #include "cpuid.h"
 #elif defined (__arm__)
  #define nehalem_available 0
#endif

const std::string ENV_PCI_DEVICE_ID = "DBUS_PCI_DEVICE_ID";
const std::string envPciDeviceId = std::getenv(ENV_PCI_DEVICE_ID.c_str());
const int DEFAULT_NDCTL_PORT = 9090;

// Function to check if NMEM is available
bool isNMEMAvailable() {
    std::string checkNMEM = "lnctl isenabled //nmem 2>&1 | grep Enabled";
    int exitStatus = system(checkNMEM.c_str());
    return exitStatus == 0;
}
// Function to persist data to NMEM using direct access
bool persistDataToNMEM(const void* data, size_t size, uint64_t address) {
    if (!isNMEMAvailable()) {
        std::cerr << "NMEM is not available on this system." << std::endl;
        return false;
    }

    int fd = open("/dev/daxctl", O_RDWR);
    if (fd == -1) {
        perror("Error opening /dev/daxctl");
        return false;
    }

    struct daxctl_region info;
    memset(&info, 0, sizeof(info));
    info.mem_id = 0; // Use NMEM

    if (ioctl(fd, DAXCTL_GET_REGION, &info) == -1) {
        perror("Error getting NMEM region information");
        close(fd);
        return false;
    }

    if (address >= info.size) {
        std::cerr << "Specified NMEM address is out of bounds." << std::endl;
        close(fd);
        return false;
    }

    void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, address);
    if (ptr == MAP_FAILED) {
        perror("Error mapping NMEM to memory");
        close(fd);
        return false;
    }

    memcpy(ptr, data, size);
    munmap(ptr, size);
    close(fd);

    std::cout << "Data persisted to NMEM at address 0x" << std::hex << address << " of size " << size << " bytes." << std::endl;
    return true;
}

// Function to retrieve data from NMEM using direct access
bool retrieveDataFromNMEM(void* data, size_t size, uint64_t address) {
    if (!isNMEMAvailable()) {
        std::cerr << "NMEM is not available on this system." << std::endl;
        return false;
    }

    int fd = open("/dev/daxctl", O_RDWR);
    if (fd == -1) {
        perror("Error opening /dev/daxctl");
        return false;
    }

    struct daxctl_region info;    
    memset(&info, 0, sizeof(info));
    info.mem_id = 0; // Use NMEM

    if (ioctl(fd, DAXCTL_GET_REGION, &info) == -1) {
        perror("Error getting NMEM region information");
