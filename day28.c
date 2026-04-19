/* Problem: Circular Linked List Creation and Traversal - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the circular linked list elements starting from head, space-separated

Example:
Input:
5
10 20 30 40 50

Output:
10 20 30 40 50

Explanation:
Last node's next points to head. Traverse from head until returning to head to avoid infinite loop.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int main() {
    int n, value;
    struct Node *head = NULL, *tail = NULL;

    // 1. Read number of elements
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    // 2. Create the Circular Linked List
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);

        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = value;
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
            newNode->next = head; // Point to itself initially
        } else {
            tail->next = newNode; // Old tail points to new node
            tail = newNode;       // New node becomes the tail
            tail->next = head;    // New tail points back to head
        }
    }

    // 3. Traverse the Circular Linked List
    if (head != NULL) {
        struct Node* temp = head;
        // Use a do-while loop to ensure we process the head before checking the condition
        do {
            printf("%d", temp->data);
            temp = temp->next;
            if (temp != head) {
                printf(" ");
            }
        } while (temp != head);
        printf("\n");
    }

    return 0;
}