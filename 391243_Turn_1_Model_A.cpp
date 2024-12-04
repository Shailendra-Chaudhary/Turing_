#include <cstdint>

// Define the size of the integer data you want to store.
#define DATA_SIZE 16

// Custom linked list node
struct Node {
    // Use int16_t for 16-bit integer data
    int16_t data;
    // Pointer to the next node
    Node* next;
};

class LinkedList {
public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void append(int16_t value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void printList() {
        Node* current = head;
        while (current != nullptr) {
            std::printf("%d -> ", current->data);
            current = current->next;
        }
        std::printf("null\n");
    }

private:
    Node* head;
};

int main() {
    LinkedList list;
    list.append(123);
    list.append(456);
    list.append(789);

    list.printList();

    return 0;
}
