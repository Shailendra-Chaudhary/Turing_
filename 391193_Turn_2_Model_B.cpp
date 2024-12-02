
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// Custom memory allocator
class CustomAllocator {
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef char value_type;

    template<typename U>
    struct rebind {
        typedef CustomAllocator<U> other;
    };

    pointer allocate(size_type n) {
        return ::operator new(n * sizeof(value_type));
    }

    void deallocate(pointer p, size_type n) {
        ::operator delete(p);
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new(static_cast<void*>(p)) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p) {
        p->~U();
    }

    CustomAllocator select_on_container_copy_construction() const {
        return *this;
    }
};

// Custom Node data structure using custom allocator
template<typename T>
class CustomNode {
public:
    T vertex;
    int distance;
    CustomNode<T>* next;

    CustomNode(T vertex, int distance) : vertex(vertex), distance(distance), next(nullptr) {}

    void* operator new(size_t size) {
        return CustomAllocator<CustomNode<T>>().allocate(size);
    }

    void operator delete(void* p) {
        CustomAllocator<CustomNode<T>>().deallocate(static_cast<CustomNode<T>*>(p), 1);
    }
};

// Custom Priority Queue using custom node and custom allocator
template<typename T>
class CustomPriorityQueue {
private:
    CustomNode<T>* head;
    int size;

public:
    CustomPriorityQueue() : head(nullptr), size(0) {}

    ~CustomPriorityQueue() {
        while (head != nullptr) {
            CustomNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(T vertex, int distance) {
        CustomNode<T>* new_node = new CustomNode<T>(vertex, distance);
        new_node->next = head;
        head = new_node;
        size++;
    }

    CustomNode<T>* remove() {
        if (is_empty()) {
            return nullptr;
        }

        CustomNode<T>* current = head;
        CustomNode<T>* prev = nullptr;
        int min_distance = current->distance;
        CustomNode<T>* min_node = current;

        while (current != nullptr) {
            if (current->distance < min_distance) {
                min_distance = current->distance;
                min_node = current;
            }
            prev = current;
            current = current->next;
        }

        if (prev == nullptr) {
            head = min_node->next;
        } else {
            prev->next = min_node->next;
        }

        size--;
        return min_node;
    }

    bool is_empty() const {
        return size == 0;
    }

    int get_size() const {
        return size;
    }
};

// Dijkstra's algorithm implementation
template<typename T>
int dijkstra(const std::vector<std::vector<int>>& graph, int start_vertex, int end_vertex) {
    int num_vertices = graph.size();
