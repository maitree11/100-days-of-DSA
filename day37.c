/* Problem Statement:
Implement a Priority Queue using an array. An element with smaller value has higher priority.

Supported Operations:
- insert x
- delete
- peek

Input Format:
- First line contains integer N
- Next N lines contain operations

Output Format:
- Print the deleted or peeked element
- Print -1 if the queue is empty

Example:
Input:
5
insert 30
insert 10
insert 20
delete
peek

Output:
10
20
*/

#include <stdio.h>
#include <string.h>

#define MAX 1000

int pq[MAX];
int size = 0;

// Helper to peek the highest priority (smallest element)
void peek() {
    if (size == 0) {
        printf("-1\n");
    } else {
        // In our sorted array, the smallest is at index 0
        printf("%d\n", pq[0]);
    }
}

// Function to insert x while maintaining sorted order
void insert(int x) {
    if (size >= MAX) return;

    int i;
    // Find position and shift elements to the right to keep array sorted
    // Elements are stored in ascending order
    for (i = size - 1; (i >= 0 && pq[i] > x); i--) {
        pq[i + 1] = pq[i];
    }
    pq[i + 1] = x;
    size++;
}

// Function to delete the highest priority element
void delete() {
    if (size == 0) {
        printf("-1\n");
    } else {
        // Smallest element is at index 0
        printf("%d\n", pq[0]);
        
        // Shift all remaining elements to the left
        for (int i = 0; i < size - 1; i++) {
            pq[i] = pq[i + 1];
        }
        size--;
    }
}

int main() {
    int n;
    char op[10];
    int val;

    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%s", op);
        if (strcmp(op, "insert") == 0) {
            scanf("%d", &val);
            insert(val);
        } else if (strcmp(op, "delete") == 0) {
            delete();
        } else if (strcmp(op, "peek") == 0) {
            peek();
        }
    }

    return 0;
}