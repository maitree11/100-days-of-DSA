/* Problem: Deque (Double-Ended Queue)

A Deque is a linear data structure that allows insertion and deletion of elements from both the front and the rear. It provides more flexibility than a standard queue or stack.

Common Operations:
1. push_front(value): Insert an element at the front of the deque.
2. push_back(value): Insert an element at the rear of the deque.
3. pop_front(): Remove an element from the front of the deque.
4. pop_back(): Remove an element from the rear of the deque.
5. front(): Return the front element of the deque.
6. back(): Return the rear element of the deque.
7. empty(): Check whether the deque is empty.
8. size(): Return the number of elements in the deque.

Additional Operations:
- clear(): Remove all elements from the deque.
- erase(): Remove one or more elements from the deque.
- swap(): Swap contents of two deques.
- emplace_front(): Insert an element at the front without copying.
- emplace_back(): Insert an element at the rear without copying.
- resize(): Change the size of the deque.
- assign(): Replace elements with new values.
- reverse(): Reverse the order of elements.
- sort(): Sort the elements in ascending order.

Time Complexity:
- push_front, push_back, pop_front, pop_back, front, back, empty, size: O(1)
- clear, erase, resize, assign, reverse: O(n)
- sort: O(n log n)

Input:
- Sequence of deque operations with values (if applicable)

Output:
- Results of operations such as front, back, size, or the final state of the deque after all operations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure
struct Node {
    int data;
    struct Node *next, *prev;
};

// Deque structure
struct Deque {
    struct Node *front, *rear;
    int size;
};

struct Deque* createDeque() {
    struct Deque* dq = (struct Deque*)malloc(sizeof(struct Deque));
    dq->front = dq->rear = NULL;
    dq->size = 0;
    return dq;
}

void push_front(struct Deque* dq, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = dq->front;
    newNode->prev = NULL;
    if (dq->front == NULL) dq->rear = newNode;
    else dq->front->prev = newNode;
    dq->front = newNode;
    dq->size++;
}

void push_back(struct Deque* dq, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = dq->rear;
    if (dq->rear == NULL) dq->front = newNode;
    else dq->rear->next = newNode;
    dq->rear = newNode;
    dq->size++;
}

int pop_front(struct Deque* dq) {
    if (dq->size == 0) return -1;
    struct Node* temp = dq->front;
    int val = temp->data;
    dq->front = dq->front->next;
    if (dq->front == NULL) dq->rear = NULL;
    else dq->front->prev = NULL;
    free(temp);
    dq->size--;
    return val;
}

int pop_back(struct Deque* dq) {
    if (dq->size == 0) return -1;
    struct Node* temp = dq->rear;
    int val = temp->data;
    dq->rear = dq->rear->prev;
    if (dq->rear == NULL) dq->front = NULL;
    else dq->rear->next = NULL;
    free(temp);
    dq->size--;
    return val;
}

void display(struct Deque* dq) {
    struct Node* temp = dq->front;
    while (temp) {
        printf("%d%s", temp->data, temp->next ? " " : "");
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n, val;
    char op[20];
    struct Deque* dq = createDeque();

    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%s", op);
        if (strcmp(op, "push_front") == 0) {
            scanf("%d", &val);
            push_front(dq, val);
        } else if (strcmp(op, "push_back") == 0) {
            scanf("%d", &val);
            push_back(dq, val);
        } else if (strcmp(op, "pop_front") == 0) {
            pop_front(dq);
        } else if (strcmp(op, "pop_back") == 0) {
            pop_back(dq);
        } else if (strcmp(op, "front") == 0) {
            if (dq->front) printf("%d\n", dq->front->data);
        } else if (strcmp(op, "back") == 0) {
            if (dq->rear) printf("%d\n", dq->rear->data);
        } else if (strcmp(op, "size") == 0) {
            printf("%d\n", dq->size);
        }
    }
    
    display(dq);
    return 0;
}