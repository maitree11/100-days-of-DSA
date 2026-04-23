/* Problem Statement:
Convert a binary tree into its mirror image by swapping left and right children at every node.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 indicates NULL)

Output Format:
- Print inorder traversal of mirrored tree

Example:
Input:
7
1 2 3 4 5 6 7

Output:
7 3 6 1 5 2 4

Explanation:
Each node’s left and right children are swapped recursively.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int val) {
    if (val == -1) return NULL;
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

// Function to convert a tree to its mirror
void mirror(struct Node* root) {
    if (root == NULL) return;

    // Recur for subtrees
    mirror(root->left);
    mirror(root->right);

    // Swap the pointers
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
}

// Inorder traversal to verify the output
void inorder(struct Node* root, int* first) {
    if (root == NULL) return;
    inorder(root->left, first);
    
    if (!(*first)) printf(" ");
    printf("%d", root->data);
    *first = 0;
    
    inorder(root->right, first);
}

// Helper to build tree from level-order input
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
    
    mirror(root);
    
    int first = 1;
    inorder(root, &first);
    printf("\n");

    return 0;
}