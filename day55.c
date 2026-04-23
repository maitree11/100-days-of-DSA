/* Problem Statement:
Print the nodes visible when the binary tree is viewed from the right side.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 indicates NULL)

Output Format:
- Print right view nodes

Example:
Input:
7
1 2 3 4 5 -1 6

Output:
1 3 6

Explanation:
At each level, the rightmost node is visible from the right view.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Helper to create a new node
struct Node* newNode(int val) {
    if (val == -1) return NULL;
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

// Function to calculate Right View recursively
void getRightView(struct Node* root, int level, int* maxLevel, int* first) {
    if (root == NULL) return;

    // If this is the first node of this level (from the right)
    if (*maxLevel < level) {
        if (!(*first)) printf(" ");
        printf("%d", root->data);
        *maxLevel = level;
        *first = 0;
    }

    // Recur for right subtree first so we "hit" the rightmost nodes
    getRightView(root->right, level + 1, maxLevel, first);
    getRightView(root->left, level + 1, maxLevel, first);
}

// Standard Level-order tree construction
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    struct Node* root = newNode(arr[0]);
    struct Node** q = (struct Node**)malloc(sizeof(struct Node*) * n);
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

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    struct Node* root = buildTree(arr, n);
    
    int maxLevel = 0;
    int first = 1;
    getRightView(root, 1, &maxLevel, &first);
    printf("\n");

    return 0;
}