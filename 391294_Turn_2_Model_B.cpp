// file: asan_example.cpp
#include <cstring>
#include <iostream>

void bufferOverflow() {
    char buffer[5];
    std::strcpy(buffer, "HelloWorld");  // Intentional buffer overflow
    std::cout << "Buffer content: " << buffer << std::endl;
}

void useAfterFree() {
    int* data = new int[100];
    delete[] data;
    data[0] = 42;  // Intentional use-after-free
    std::cout << "Data: " << data[0] << std::endl;
}

int main() {
    bufferOverflow();
    useAfterFree();
    return 0;
}
