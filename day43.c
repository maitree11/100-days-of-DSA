/* Problem Statement:
Construct a Binary Tree from the given level-order traversal.

Input Format:
- First line contains integer N
- Second line contains N space-separated integers (-1 represents NULL)

Output Format:
- Print inorder traversal of the constructed tree

Example:
Input:
7
1 2 3 4 5 -1 6

Output:
4 2 5 1 3 6
*/

#include <stdio.h>
#include <stdlib.h>

// Binary Tree Node
struct Node {
    int data;
    struct Node *left, *right;
};

// Queue for Level-Order Construction
struct QueueNode {
    struct Node* treeNode;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode *front, *rear;
};

// --- Helper Functions ---
struct Node* newNode(int val) {
    if (val == -1) return NULL;
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

void enqueue(struct Queue* q, struct Node* tNode) {
    if (tNode == NULL) return;
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->treeNode = tNode;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

struct Node* dequeue(struct Queue* q) {
    if (q->front == NULL) return NULL;
    struct QueueNode* temp = q->front;
    struct Node* tNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return tNode;
}

// --- Tree Construction ---
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    struct Queue q = {NULL, NULL};
    struct Node* root = newNode(arr[0]);
    enqueue(&q, root);

    int i = 1;
    while (i < n) {
        struct Node* parent = dequeue(&q);

        // Left Child
        if (i < n) {
            parent->left = newNode(arr[i++]);
            if (parent->left) enqueue(&q, parent->left);
        }

        // Right Child
        if (i < n) {
            parent->right = newNode(arr[i++]);
            if (parent->right) enqueue(&q, parent->right);
        }
    }
    return root;
}

// --- Inorder Traversal ---
void inorder(struct Node* root, int* first) {
    if (root == NULL) return;
    inorder(root->left, first);
    
    if (!(*first)) printf(" ");
    printf("%d", root->data);
    *first = 0;
    
    inorder(root->right, first);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct Node* root = buildTree(arr, n);
    int first = 1;
    inorder(root, &first);
    printf("\n");

    return 0;
}