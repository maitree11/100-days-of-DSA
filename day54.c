/* Problem Statement:
Perform zigzag (spiral) level order traversal of a binary tree. Alternate levels should be traversed left-to-right and right-to-left.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 indicates NULL)

Output Format:
- Print traversal in zigzag order

Example:
Input:
7
1 2 3 4 5 6 7

Output:
1 3 2 4 5 6 7

Explanation:
Level 1 is printed left-to-right, level 2 right-to-left, and so on.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Simple Stack implementation for Tree Nodes
struct Stack {
    struct Node **arr;
    int top;
};

struct Stack* createStack(int n) {
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
    s->arr = (struct Node**)malloc(n * sizeof(struct Node*));
    s->top = -1;
    return s;
}

void push(struct Stack* s, struct Node* node) {
    if (node) s->arr[++(s->top)] = node;
}

struct Node* pop(struct Stack* s) {
    return (s->top == -1) ? NULL : s->arr[(s->top)--];
}

int isEmpty(struct Stack* s) {
    return s->top == -1;
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
    struct Node** q = (struct Node**)malloc(n * sizeof(struct Node*));
    int front = 0, rear = 0;
    q[rear++] = root;
    int i = 1;
    while (i < n) {
        struct Node* curr = q[front++];
        if (i < n) {
            curr->left = newNode(arr[i++]);
            if (curr->left) q[rear++] = curr->left;
        }
        if (i < n) {
            curr->right = newNode(arr[i++]);
            if (curr->right) q[rear++] = curr->right;
        }
    }
    return root;
}

void zigzagTraversal(struct Node* root, int n) {
    if (!root) return;

    struct Stack* s1 = createStack(n); // Left to Right
    struct Stack* s2 = createStack(n); // Right to Left

    push(s1, root);
    int first = 1;

    while (!isEmpty(s1) || !isEmpty(s2)) {
        // Process current level Left to Right
        while (!isEmpty(s1)) {
            struct Node* curr = pop(s1);
            if (!first) printf(" ");
            printf("%d", curr->data);
            first = 0;

            // Push children to s2: Left then Right
            if (curr->left) push(s2, curr->left);
            if (curr->right) push(s2, curr->right);
        }

        // Process next level Right to Left
        while (!isEmpty(s2)) {
            struct Node* curr = pop(s2);
            printf(" %d", curr->data);

            // Push children to s1: Right then Left
            if (curr->right) push(s1, curr->right);
            if (curr->left) push(s1, curr->left);
        }
    }
    printf("\n");
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    struct Node* root = buildTree(arr, n);
    zigzagTraversal(root, n);

    return 0;
}