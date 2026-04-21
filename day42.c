/* Problem Statement:
Given a queue of integers, reverse the queue using a stack.

Input Format:
- First line contains integer N
- Second line contains N space-separated integers

Output Format:
- Print the reversed queue

Example:
Input:
5
10 20 30 40 50

Output:
50 40 30 20 10
*/

#include <stdio.h>
#include <stdlib.h>

// Standard Node for both Stack and Queue
struct Node {
    int data;
    struct Node* next;
};

// Queue Pointers
struct Queue {
    struct Node *front, *rear;
};

// Stack Pointer
struct Stack {
    struct Node* top;
};

// --- Stack Operations ---
void push(struct Stack* s, int x) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(struct Stack* s) {
    if (s->top == NULL) return -1;
    struct Node* temp = s->top;
    int val = temp->data;
    s->top = s->top->next;
    free(temp);
    return val;
}

// --- Queue Operations ---
void enqueue(struct Queue* q, int x) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(struct Queue* q) {
    if (q->front == NULL) return -1;
    struct Node* temp = q->front;
    int val = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return val;
}

// --- Reversal Logic ---
void reverseQueue(struct Queue* q) {
    struct Stack s = {NULL};

    // Phase 1: Dequeue everything and push to Stack
    while (q->front != NULL) {
        push(&s, dequeue(q));
    }

    // Phase 2: Pop from Stack and enqueue back
    while (s.top != NULL) {
        enqueue(q, pop(&s));
    }
}

int main() {
    int n, val;
    struct Queue q = {NULL, NULL};

    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        enqueue(&q, val);
    }

    reverseQueue(&q);

    // Print the reversed queue
    struct Node* curr = q.front;
    while (curr) {
        printf("%d%s", curr->data, curr->next ? " " : "");
        curr = curr->next;
    }
    printf("\n");

    return 0;
}