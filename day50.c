/* Problem: BST Search

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

struct Node* newNode(int val) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert nodes to build the tree for testing
struct Node* insert(struct Node* root, int val) {
    if (root == NULL) return newNode(val);
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}

// Recursive Search Function
struct Node* search(struct Node* root, int key) {
    // Base Case: root is null or key is present at root
    if (root == NULL || root->data == key) {
        return root;
    }

    // Key is greater than root's data
    if (key > root->data) {
        return search(root->right, key);
    }

    // Key is smaller than root's data
    return search(root->left, key);
}

int main() {
    int n, key, val;
    struct Node* root = NULL;

    // Input number of nodes and build the BST
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    // Input the value to search for
    scanf("%d", &key);

    struct Node* result = search(root, key);

    if (result != NULL) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    return 0;
}