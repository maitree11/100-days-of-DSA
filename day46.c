/* Problem: Level Order Traversal

Implement the solution for this problem.

Input:
- Input specifications

Output:
- Output specifications
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Queue for Tree Nodes
struct Queue {
    struct Node **arr;
    int front, rear, capacity;
};

struct Queue* createQueue(int size) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->capacity = size;
    q->front = q->rear = 0;
    q->arr = (struct Node**)malloc(size * sizeof(struct Node*));
    return q;
}

void enqueue(struct Queue* q, struct Node* node) {
    if (node) q->arr[q->rear++] = node;
}

struct Node* dequeue(struct Queue* q) {
    return (q->front == q->rear) ? NULL : q->arr[q->front++];
}

struct Node* newNode(int val) {
    if (val == -1) return NULL;
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

// Build tree from level-order input
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    struct Node* root = newNode(arr[0]);
    struct Queue* q = createQueue(n);
    enqueue(q, root);
    int i = 1;
    while (i < n) {
        struct Node* curr = dequeue(q);
        if (i < n) {
            curr->left = newNode(arr[i++]);
            enqueue(q, curr->left);
        }
        if (i < n) {
            curr->right = newNode(arr[i++]);
            enqueue(q, curr->right);
        }
    }
    return root;
}

// Actual Level Order Traversal Function
void levelOrder(struct Node* root, int n) {
    if (!root) return;
    struct Queue* q = createQueue(n);
    enqueue(q, root);
    
    int first = 1;
    while (q->front != q->rear) {
        struct Node* curr = dequeue(q);
        
        if (!first) printf(" ");
        printf("%d", curr->data);
        first = 0;
        
        if (curr->left) enqueue(q, curr->left);
        if (curr->right) enqueue(q, curr->right);
    }
    printf("\n");
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    struct Node* root = buildTree(arr, n);
    levelOrder(root, n);

    return 0;
}