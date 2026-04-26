// Problem: Implement topological sorting using in-degree array and queue (Kahnâ€™s Algorithm).

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* inDegree;
};

struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct Node*));
    graph->inDegree = calloc(vertices, sizeof(int));
    for (int i = 0; i < vertices; i++) graph->adjLists[i] = NULL;
    return graph;
}

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = graph->adjLists[u];
    graph->adjLists[u] = newNode;
    graph->inDegree[v]++; // Increment in-degree of destination
}

void kahnsTopologicalSort(struct Graph* graph) {
    int* queue = malloc(graph->numVertices * sizeof(int));
    int* result = malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0, count = 0;

    // 1. Add all nodes with 0 in-degree to queue
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // 2. Process the queue
    while (front < rear) {
        int u = queue[front++];
        result[count++] = u;

        struct Node* temp = graph->adjLists[u];
        while (temp) {
            int v = temp->vertex;
            graph->inDegree[v]--; // "Remove" edge u -> v
            
            if (graph->inDegree[v] == 0) {
                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }

    // 3. Output result or detect cycle
    if (count != graph->numVertices) {
        printf("Cycle detected! Topological sort not possible.\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("%d%s", result[i], (i == count - 1) ? "" : " ");
        }
        printf("\n");
    }

    free(queue);
    free(result);
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    struct Graph* graph = createGraph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    kahnsTopologicalSort(graph);

    return 0;
}