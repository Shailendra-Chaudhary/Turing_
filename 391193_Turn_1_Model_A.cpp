#include <limits>

struct Node {
    int x, y, cost;
    Node* parent;

    bool operator<(const Node& other) const {
        return cost < other.cost;
    }
};

void aStar(int width, int height, int startX, int startY, int endX, int endY) {
    // Static array for priority queue (assuming limits are known)
    Node pq[width * height];
    int pqIndex = 0;

    int gScore[width][height] = {};
    int fScore[width][height] = {};

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            gScore[i][j] = std::numeric_limits<int>::max();
            fScore[i][j] = std::numeric_limits<int>::max();
        }
    }

    gScore[startX][startY] = 0;
    fScore[startX][startY] = manhattanDistance(startX, startY, endX, endY);

    pq[pqIndex++] = {startX, startY, fScore[startX][startY]};

    while (pqIndex > 0) {
        int currentX = pq[0].x, currentY = pq[0].y;
        --pqIndex;
        pq[pqIndex] = pq[0];
        --pqIndex;

        // Check if reached the destination
        if (currentX == endX && currentY == endY) {
            reconstructPath(currentX, currentY, pq);
            return;
        }

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int newX = currentX + dx, newY = currentY + dy;
                if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                    int tentativeGScore = gScore[currentX][currentY] + 1;
                    if (tentativeGScore < gScore[newX][newY]) {
                        gScore[newX][newY] = tentativeGScore;
                        fScore[newX][newY] = gScore[newX][newY] + manhattanDistance(newX, newY, endX, endY);

                        // Add to priority queue
                        bool found = false;
                        for (int i = 0; i < pqIndex; ++i) {
                            if (pq[i].x == newX && pq[i].y == newY) {
                                pq[i].cost = fScore[newX][newY];
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            pq[pqIndex++] = {newX, newY, fScore[newX][newY]};
                            // Sort the priority queue
                            int i = pqIndex - 1;
                            while (i > 0 && pq[i].cost < pq[(i - 1) / 2].cost) {
                                std::swap(pq[i], pq[(i - 1) / 2]);
                                i = (i - 1) / 2;
                            }
                        }
                    }
                }
            }
        }
    }

    // No path found
}

// Helper functions
int manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void reconstructPath(int x, int y, Node* pq) {
    int pathX[width * height] = {};
    int pathY[width * height] = {};
    int pathIndex = 0;
    pathX[pathIndex] = x;
    pathY[pathIndex] = y;
    Node* current = &pq[0];
    while (current->parent) {
        current = current->parent;
        pathX[pathIndex++] = current->x;
        pathY[pathIndex] = current->y;
    }

    // Print or use the path as needed
}

int main() {
    int width = 10, height = 10;
    aStar(width, height, 0, 0, width - 1, height - 1);
    return 0;
}
