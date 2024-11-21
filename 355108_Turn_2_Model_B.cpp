#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Example of a game entity
struct Entity {
    int id;
    float positionX, positionY;
};

int main() {
    // 1. Use reserve() to preallocate memory
    vector<Entity> entities;
    entities.reserve(1000); // Preallocate memory for 1000 entities

    // 2. Use move semantics instead of copy semantics
    for (int i = 0; i < 1000; ++i) {
        entities.emplace_back(i, i * 0.1f, i * 0.01f); // emplace_back uses move
    }

    // 3. Use iterators or ranges for efficient loops
    float totalX = 0;
    for (const Entity& entity : entities) {
        totalX += entity.positionX;
    }

    // 4. Use std::sort() with custom comparator for sorting
    std::sort(entities.begin(), entities.end(), [](const Entity& lhs, const Entity& rhs) {
        return lhs.positionY < rhs.positionY;
    });

    // 5. Avoid unnecessary reallocations by resizing the container before inserting/removing a large number of elements at the back
    entities.resize(entities.size() + 500); // Assuming you need to add more entities
    for (int i = 1000; i < 1500; ++i) {
        entities.emplace_back(i, i * 0.1f, i * 0.01f);
    }

    // 6. Use containers with optimized memory layout for specific use cases
    // e.g., std::deque for fast insertions/removals at both ends, std::unordered_map for fast lookups

    // 7. Profile and optimize as needed
    // Use profiling tools to identify bottlenecks and optimize specific parts of the code accordingly

    cout << "Total X position: " << totalX << endl;

    return 0;
}
