/* Problem: Build a graph with adjacency list representation. Use linked lists or dynamic arrays.

Input:
- n (vertices)
- m (edges)
- edges (u, v)

Output:
- List of adjacency lists for each vertex
*/

#include <stdio.h>
#include <stdlib.h>

// Node representing an edge in the linked list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure representing the Adjacency List for each vertex
struct AdjList {
    struct Node* head;
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

int main() {
    int n, m, isDirected;

    // Input: Vertices, Edges, and Type (1 for Directed, 0 for Undirected)
    if (scanf("%d %d %d", &n, &m, &isDirected) != 3) return 0;

    // Allocate array of adjacency lists
    struct AdjList* adjLists = (struct AdjList*)malloc(n * sizeof(struct AdjList));
    for (int i = 0; i < n; i++) {
        adjLists[i].head = NULL;
    }

    // Input m edges
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        // Add edge u -> v
        struct Node* newNode = createNode(v);
        newNode->next = adjLists[u].head;
        adjLists[u].head = newNode;

        // If undirected, add edge v -> u
        if (!isDirected) {
            newNode = createNode(u);
            newNode->next = adjLists[v].head;
            adjLists[v].head = newNode;
        }
    }

    // Output: Print Adjacency Lists
    for (int i = 0; i < n; i++) {
        printf("%d:", i);
        struct Node* temp = adjLists[i].head;
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }

    return 0;
}