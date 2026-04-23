/* Problem Statement:
Check whether a given binary tree is symmetric around its center.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 indicates NULL)

Output Format:
- Print YES if symmetric, otherwise NO

Example:
Input:
7
1 2 2 3 4 4 3

Output:
YES

Explanation:
Left subtree is a mirror image of the right subtree.
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

// Function to check if two trees are mirror images
int isMirror(struct Node* t1, struct Node* t2) {
    // If both are null, they are mirrors
    if (t1 == NULL && t2 == NULL) return 1;
    
    // If only one is null, they are not mirrors
    if (t1 == NULL || t2 == NULL) return 0;
    
    // Check if current values match and subtrees are mirrored
    return (t1->data == t2->data) &&
           isMirror(t1->left, t2->right) &&
           isMirror(t1->right, t2->left);
}

int isSymmetric(struct Node* root) {
    if (root == NULL) return 1;
    return isMirror(root->left, root->right);
}

// Build tree from level-order input
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
    
    if (isSymmetric(root)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}