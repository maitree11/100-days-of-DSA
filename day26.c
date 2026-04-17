/* Problem: Doubly Linked List Insertion and Traversal - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the linked list elements in forward order, space-separated

Example:
Input:
5
10 20 30 40 50

Output:
10 20 30 40 50

Explanation:
Each node has data, next, prev. Insert nodes sequentially, traverse from head using next pointer. 
*/

#include <stdio.h>
#include <stdlib.h>

// Structure for a Doubly Linked List node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

int main() {
    int n, value;
    struct Node *head = NULL, *tail = NULL;

    // 1. Read number of elements
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    // 2. Create and Insert nodes
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);

        // Allocate memory for the new node
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = value;
        newNode->next = NULL;
        newNode->prev = NULL;

        if (head == NULL) {
            // First node: both head and tail point here
            head = newNode;
            tail = newNode;
        } else {
            // Link the new node to the end of the list
            tail->next = newNode;    // Current tail points forward to newNode
            newNode->prev = tail;    // NewNode points backward to current tail
            tail = newNode;          // Move tail to the new end
        }
    }

    // 3. Traverse Forward
    struct Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");

    return 0;
}