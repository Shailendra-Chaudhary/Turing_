#include <iostream>
#include <vector>
#include <limits.h>

// Custom priority queue (min-heap)
struct PriorityQueue {
    std::vector<int> heap; // Stores indices of vertices in the graph
    std::vector<int> distances; // Stores distances from start vertex

    void push(int vertex, int distance) {
        distances[vertex] = distance;
        heap.push_back(vertex);
        siftUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;
        heap.swap_back(0);
        heap.pop_back();
        siftDown(0);
    }

    int top() const {
        return heap.empty() ? -1 : heap[0];
    }

    bool empty() const {
        return heap.empty();
    }

private:
    void siftUp(int index) {
        while (index > 0 && distances[heap[index]] < distances[heap[(index - 1) / 2]]) {
            std::swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void siftDown(int index) {
        int size = heap.size();
        while (index * 2 + 1 < size) {
            int childIndex = index * 2 + 1;
            if (childIndex + 1 < size && distances[heap[childIndex + 1]] < distances[heap[childIndex]]) {
                childIndex++;
            }
            if (distances[heap[index]] <= distances[heap[childIndex]]) {
                break;
            }
            std::swap(heap[index], heap[childIndex]);
            index = childIndex;
        }
    }
};

// Custom graph data structure using an adjacency list
struct Graph {
    std::vector<std::vector<int>> edges;

    Graph(int numVertices) : edges(numVertices) {}

    void addEdge(int src, int dest, int weight) {
        edges[src].push_back({dest, weight});
        edges[dest].push_back({src, weight}); // Assuming an undirected graph
    }
};

// Dijkstra's algorithm
void dijkstra(Graph& graph, int numVertices, int startVertex) {
    PriorityQueue pq;
    std::vector<int> distances(numVertices, INT_MAX);
    distances[startVertex] = 0;

    pq.push(startVertex, 0);

    while (!pq.empty()) {
        int currentVertex = pq.pop();

        for (const auto& edge : graph.edges[currentVertex]) {
            int neighbor = edge.first;
            int weight = edge.second;

            if (distances[neighbor] > distances[currentVertex] + weight) {
                distances[neighbor] = distances[currentVertex] + weight;
                pq.push(neighbor, distances[neighbor]);
            }
        }
    }

    // Print distances
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "Distance from vertex " << startVertex << " to vertex " << i << ": " << distances[i] << std::endl;
    }
}

int main() {
    int numVertices = 4;
    Graph graph(numVertices);

    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 10);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 2);

    int startVertex = 0;
    dijkstra(graph, numVertices, startVertex);

    return 0;
}
