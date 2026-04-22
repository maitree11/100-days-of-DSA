/* Problem: BST Insert

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
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

// Recursive function to insert a value into the BST
struct Node* insert(struct Node* root, int val) {
    // If the tree/subtree is empty, return a new node
    if (root == NULL) {
        return newNode(val);
    }

    // Otherwise, recur down the tree
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }

    // Return the (unchanged) node pointer
    return root;
}

// Inorder traversal to verify the BST (should print in ascending order)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    int n, val;
    struct Node* root = NULL;

    // Input: Number of elements to insert
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    // Output: Print inorder traversal to show sorted result
    inorder(root);
    printf("\n");

    return 0;
}