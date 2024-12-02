#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int vertex;
    int distance;
} Node;

typedef struct {
    Node* nodes;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* create_priority_queue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->nodes = (Node*)malloc(capacity * sizeof(Node));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void destroy_priority_queue(PriorityQueue* pq) {
    free(pq->nodes);
    free(pq);
}

void swap_nodes(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(PriorityQueue* pq, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && pq->nodes[index].distance < pq->nodes[parent].distance) {
        swap_nodes(&pq->nodes[index], &pq->nodes[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void heapify_down(PriorityQueue* pq, int index) {
    int child = 2 * index + 1;
    while (child < pq->size) {
        if (child + 1 < pq->size && pq->nodes[child + 1].distance < pq->nodes[child].distance) {
            child++;
        }
        if (pq->nodes[index].distance < pq->nodes[child].distance) {
            break;
        }
        swap_nodes(&pq->nodes[index], &pq->nodes[child]);
        index = child;
        child = 2 * index + 1;
    }
}

void insert_node(PriorityQueue* pq, int vertex, int distance) {
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->nodes = (Node*)realloc(pq->nodes, pq->capacity * sizeof(Node));
    }
    Node node = {vertex, distance};
    pq->nodes[pq->size] = node;
    heapify_up(pq, pq->size);
    pq->size++;
}

Node remove_node(PriorityQueue* pq) {
    if (pq->size == 0) {
        Node node = {-1, INT_MAX};
        return node;
    }
    Node root = pq->nodes[0];
    pq->nodes[0] = pq->nodes[pq->size - 1];
    pq->size--;
    heapify_down(pq, 0);
    return root;
}

int dijkstra(int graph[][100], int num_vertices, int start_vertex) {
    int distances[100];
    for (int i = 0; i < num_vertices; i++) {
        distances[i] = INT_MAX;
    }
    distances[start_vertex] = 0;
    PriorityQueue* pq = create_priority_queue(num_vertices);
    insert_node(pq, start_vertex, 0);
    while (pq->size > 0) {
        Node current_node = remove_node(pq);
        int current_vertex = current_node.vertex;
        for (int i = 0; i < num_vertices; i++) {
            if (graph[current_vertex][i] != 0 && distances[i] > distances[current_vertex] + graph[current_vertex][i]) {
                distances[i] = distances[current_vertex] + graph[current_vertex][i];
                insert_node(pq, i, distances[i]);
            }
        }
    }
    destroy_priority_queue(pq);
    return distances[num_vertices - 1];
}

int main() {
    int graph[100][100] = {
        {0, 5, 0, 10},
        {0, 0, 3, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    int num_vertices = 4;
    int start_vertex = 0;
    int distance = dijkstra(graph, num_vertices, start_vertex);
    printf("Distance from vertex 0 to vertex 3: %d\n", distance);
    return 0;
}
