/* Problem Statement:
Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Search Tree.

Input Format:
- First line contains integer N
- Second line contains N space-separated integers
- Third line contains two node values

Output Format:
- Print the LCA value

Example:
Input:
7
6 2 8 0 4 7 9
2 8

Output:
6
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

// Standard BST Insert
struct Node* insert(struct Node* root, int val) {
    if (root == NULL) return newNode(val);
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}

// Function to find LCA in BST
struct Node* findLCA(struct Node* root, int n1, int n2) {
    if (root == NULL) return NULL;

    // If both n1 and n2 are smaller than root, LCA is in left
    if (root->data > n1 && root->data > n2)
        return findLCA(root->left, n1, n2);

    // If both n1 and n2 are greater than root, LCA is in right
    if (root->data < n1 && root->data < n2)
        return findLCA(root->right, n1, n2);

    // We have found the split point
    return root;
}

int main() {
    int n, val1, val2, temp;
    struct Node* root = NULL;

    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        root = insert(root, temp);
    }

    scanf("%d %d", &val1, &val2);

    struct Node* lca = findLCA(root, val1, val2);
    if (lca) printf("%d\n", lca->data);

    return 0;
}