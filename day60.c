/* Problem Statement:
Check whether a given binary tree satisfies the Min-Heap property.

Input Format:
- First line contains integer N
- Second line contains level-order traversal

Output Format:
- Print YES if valid Min-Heap, otherwise NO

Example:
Input:
7
1 3 5 7 9 8 10

Output:
YES

Explanation:
Each parent node must be smaller than its children.
*/

#include <stdio.h>
#include <stdlib.h>

int isMinHeap(int arr[], int n) {
    // We only need to check nodes that have at least one child
    // Internal nodes are from index 0 to (n-2)/2
    for (int i = 0; i <= (n - 2) / 2; i++) {
        
        // Check Left Child
        int left = 2 * i + 1;
        if (left < n && arr[i] > arr[left]) {
            return 0; // Parent is larger than left child
        }

        // Check Right Child
        int right = 2 * i + 2;
        if (right < n && arr[i] > arr[right]) {
            return 0; // Parent is larger than right child
        }
    }
    return 1;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Note: If the input contains -1, the tree might not be complete.
    // This logic assumes a complete binary tree as per standard heap problems.
    if (isMinHeap(arr, n)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    free(arr);
    return 0;
}