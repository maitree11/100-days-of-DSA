/* Problem: Detect cycle in directed graph using DFS and recursion stack.

Output:
- YES if cycle exists
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
    int* recStack; // Tracks nodes in the current recursion path
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
    graph->visited = malloc(vertices * sizeof(int));
    graph->recStack = malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
        graph->recStack[i] = 0;
    }
    return graph;
}

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = graph->adjLists[u];
    graph->adjLists[u] = newNode;
}

// DFS function to detect cycle in directed graph
int isCycleUtil(struct Graph* graph, int v) {
    if (graph->visited[v] == 0) {
        // Mark current node as visited and add to recursion stack
        graph->visited[v] = 1;
        graph->recStack[v] = 1;

        struct Node* temp = graph->adjLists[v];
        while (temp) {
            int neighbor = temp->vertex;
            
            // If not visited, recurse. If it returns 1, cycle found.
            if (!graph->visited[neighbor] && isCycleUtil(graph, neighbor))
                return 1;
            // If neighbor is already in the current recursion path, cycle!
            else if (graph->recStack[neighbor])
                return 1;
            
            temp = temp->next;
        }
    }
    // Remove node from recursion stack before backtracking
    graph->recStack[v] = 0;
    return 0;
}

int hasCycle(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (isCycleUtil(graph, i))
            return 1;
    }
    return 0;
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

    if (hasCycle(graph)) printf("YES\n");
    else printf("NO\n");

    return 0;
}