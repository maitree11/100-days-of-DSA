/* Problem: Build a graph with n vertices and m edges using adjacency matrix representation.
The graph may be directed or undirected.

Input:
- n (vertices)
- m (edges)
- m pairs (u, v)

Output:
- n x n adjacency matrix
*/

#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d%s", matrix[i][j], (j == n - 1) ? "" : " ");
        }
        printf("\n");
    }
}

int main() {
    int n, m, isDirected;
    
    // Input: Number of vertices and edges
    // Also input 1 for Directed, 0 for Undirected
    if (scanf("%d %d %d", &n, &m, &isDirected) != 3) return 0;

    // Dynamically allocate n x n matrix
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)calloc(n, sizeof(int)); // calloc initializes to 0
    }

    // Input m edges
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Assuming 0-based indexing for vertices
        if (u < n && v < n) {
            matrix[u][v] = 1;
            if (!isDirected) {
                matrix[v][u] = 1;
            }
        }
    }

    printMatrix(matrix, n);

    // Free memory
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);

    return 0;
}