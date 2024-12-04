#include <stddef.h>

// Define a structure for each memory block
struct MemoryBlock {
    void* data;
    size_t size;
    struct MemoryBlock* next;
};

// Global free memory list
MemoryBlock* freeList = nullptr;

// Function to initialize memory management system
void initializeMemoryManager(void* heapBase, size_t heapSize) {
    freeList = new MemoryBlock;
    freeList->data = heapBase;
    freeList->size = heapSize;
    freeList->next = nullptr;
}

// Function to allocate memory from the free list
void* allocateMemory(size_t size) {
    if (size == 0) return nullptr;

    // Find a block large enough to fit the request
    MemoryBlock* current = freeList;
    MemoryBlock* next;

    while (current) {
        next = current->next;
        if (current->size >= size) {
            // Split the block if it's larger than required
            if (current->size > size) {
                MemoryBlock* newBlock = new MemoryBlock;
                newBlock->data = (char*)current->data + size;
                newBlock->size = current->size - size;
                newBlock->next = current->next;
                current->size = size;
                current->next = newBlock;
            }

            // Return the block
            return current->data;
        }
        current = next;
    }

    // No suitable block found
    return nullptr;
}

// Function to deallocate memory and consolidate free blocks
void deallocateMemory(void* ptr) {
    if (ptr == nullptr) return;

    // Find the block to free
    MemoryBlock* current = freeList;
    MemoryBlock* previous = nullptr;

    while (current) {
        if (current->data == ptr) {
            if (previous) {
                previous->next = current->next;
            } else {
                freeList = current->next;
            }
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Function to compact free memory (not used in this simple example)
void compactMemory() {
    // Implement a memory compaction algorithm if needed
}

// Example usage
int main() {
    const size_t heapSize = 4096; // Example heap size
    char* heapBase = new char[heapSize];

    initializeMemoryManager(heapBase, heapSize);

    char* ptr1 = (char*)allocateMemory(100);
    char* ptr2 = (char*)allocateMemory(200);

    if (ptr1 && ptr2) {
        deallocateMemory(ptr1);
    }

    return 0;
}
