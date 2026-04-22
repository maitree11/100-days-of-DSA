/* Problem: Count Leaf Nodes

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

// Function to create a new node
struct Node* newNode(int val) {
    if (val == -1) return NULL;
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

// Function to count leaf nodes
int countLeafNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    // If a node has no children, it is a leaf
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    // Otherwise, sum the leaves from both sides
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Helper to build tree from level-order input
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    struct Node* root = newNode(arr[0]);
    struct Node** queue = (struct Node**)malloc(sizeof(struct Node*) * n);
    int front = 0, rear = 0;
    queue[rear++] = root;
    int i = 1;
    while (i < n) {
        struct Node* parent = queue[front++];
        if (i < n) {
            parent->left = newNode(arr[i++]);
            if (parent->left) queue[rear++] = parent->left;
        }
        if (i < n) {
            parent->right = newNode(arr[i++]);
            if (parent->right) queue[rear++] = parent->right;
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
    printf("%d\n", countLeafNodes(root));

    return 0;
}