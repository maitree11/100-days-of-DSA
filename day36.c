/* Problem: Circular Queue Using Array - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n (number of elements to enqueue)
- Second line: n space-separated integers
- Third line: integer m (number of dequeue operations)

Output:
- Print queue elements from front to rear after operations, space-separated

Example:
Input:
5
10 20 30 40 50
2

Output:
30 40 50 10 20

Explanation:
Use array and front/rear pointers. Rear wraps around to start after reaching array end. Dequeue removes elements from front. Display remaining elements in correct order.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct CircularQueue {
    struct Node *front, *rear;
};

// Initialize the queue
struct CircularQueue* createQueue() {
    struct CircularQueue* q = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    q->front = q->rear = NULL;
    return q;
}

// Add element to circular queue
void enqueue(struct CircularQueue* q, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    
    if (q->front == NULL) {
        q->front = newNode;
    } else {
        q->rear->next = newNode;
    }
    
    q->rear = newNode;
    q->rear->next = q->front; // Making it circular
}

// Remove element from circular queue
void dequeue(struct CircularQueue* q) {
    if (q->front == NULL) return;

    if (q->front == q->rear) {
        free(q->front);
        q->front = q->rear = NULL;
    } else {
        struct Node* temp = q->front;
        q->front = q->front->next;
        q->rear->next = q->front; // Update circular link
        free(temp);
    }
}

// Display from front to rear
void display(struct CircularQueue* q) {
    if (q->front == NULL) return;

    struct Node* temp = q->front;
    do {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp != q->front) printf(" ");
    } while (temp != q->front);
    printf("\n");
}

int main() {
    int n, m, val;
    struct CircularQueue* q = createQueue();

    // 1. Enqueue n elements
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        enqueue(q, val);
    }

    // 2. Dequeue m elements
    if (scanf("%d", &m) != 1) return 0;
    for (int i = 0; i < m; i++) {
        dequeue(q);
    }

    // 3. Display
    display(q);

    return 0;
}