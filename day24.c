/* Problem: Delete First Occurrence of a Key - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers
- Third line: integer key

Output:
- Print the linked list elements after deletion, space-separated

Example:
Input:
5
10 20 30 40 50
30

Output:
10 20 40 50

Explanation:
Traverse list, find first node with key, remove it by adjusting previous node's next pointer.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Helper function to build the list
struct Node* buildList(int n) {
    if (n <= 0) return NULL;
    struct Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = val;
        newNode->next = NULL;
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// Logic to delete the first occurrence of key
struct Node* deleteKey(struct Node* head, int key) {
    struct Node *temp = head, *prev = NULL;

    // Case 1: The head node itself holds the key
    if (temp != NULL && temp->data == key) {
        head = temp->next; // Change head
        free(temp);        // Free memory
        return head;
    }

    // Case 2: Search for the key, keep track of the previous node
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in the list
    if (temp == NULL) return head;

    // Unlink the node from the list
    prev->next = temp->next;

    // Free the memory of the deleted node
    free(temp);

    return head;
}

void printList(struct Node* head) {
    while (head) {
        printf("%d%s", head->data, head->next ? " " : "");
        head = head->next;
    }
    printf("\n");
}

int main() {
    int n, key;
    
    if (scanf("%d", &n) != 1) return 0;
    struct Node* head = buildList(n);
    
    scanf("%d", &key);
    
    head = deleteKey(head, key);
    printList(head);

    return 0;
}