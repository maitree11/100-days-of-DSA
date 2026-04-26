// Problem: Given weighted graph with non-negative edges, compute shortest path from source using priority queue.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

struct Node {
    int vertex, weight;
    struct Node* next;
};

struct Edge {
    int to, weight;
};

struct HeapNode {
    int v, dist;
};

struct MinHeap {
    int size;
    struct HeapNode* array;
};

// --- Basic Min-Heap Functions ---
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->array = malloc(capacity * sizeof(struct HeapNode));
    return minHeap;
}

void swap(struct HeapNode* a, struct HeapNode* b) {
    struct HeapNode t = *a; *a = *b; *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx, left = 2 * idx + 1, right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left].dist < minHeap->array[smallest].dist)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right].dist < minHeap->array[smallest].dist)
        smallest = right;
    if (smallest != idx) {
        swap(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

void push(struct MinHeap* minHeap, int v, int dist) {
    int i = minHeap->size++;
    minHeap->array[i].v = v;
    minHeap->array[i].dist = dist;
    while (i && minHeap->array[i].dist < minHeap->array[(i - 1) / 2].dist) {
        swap(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

struct HeapNode pop(struct MinHeap* minHeap) {
    struct HeapNode root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[--minHeap->size];
    minHeapify(minHeap, 0);
    return root;
}

// --- Dijkstra's Logic ---
void dijkstra(int n, struct Node** adj, int src) {
    int* dist = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) dist[i] = INF;

    struct MinHeap* pq = createMinHeap(n * n); // Simple capacity
    dist[src] = 0;
    push(pq, src, 0);

    while (pq->size != 0) {
        struct HeapNode current = pop(pq);
        int u = current.v;

        if (current.dist > dist[u]) continue;

        struct Node* temp = adj[u];
        while (temp) {
            int v = temp->vertex;
            int weight = temp->weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                push(pq, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) printf("Node %d: INF\n", i);
        else printf("Node %d: %d\n", i, dist[i]);
    }
}

// Helper to add edge
void addEdge(struct Node** adj, int u, int v, int w) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = adj[u];
    adj[u] = newNode;
}

int main() {
    int n, m, src;
    scanf("%d %d", &n, &m);
    struct Node** adj = calloc(n, sizeof(struct Node*));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(adj, u, v, w);
        addEdge(adj, v, u, w); // Undirected
    }
    scanf("%d", &src);
    dijkstra(n, adj, src);
    return 0;
}