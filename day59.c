/* Problem Statement:
Construct a binary tree from given inorder and postorder traversal arrays.

Input Format:
- First line contains integer N
- Second line contains inorder traversal
- Third line contains postorder traversal

Output Format:
- Print preorder traversal of constructed tree

Example:
Input:
5
4 2 5 1 3
4 5 2 3 1

Output:
1 2 4 5 3

Explanation:
Postorder gives root at end, inorder divides left and right subtrees.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

// Search for the index of a value in the inorder array
int search(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) return i;
    }
    return -1;
}

// Recursive function to build the tree
struct Node* buildTree(int inorder[], int postorder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd) return NULL;

    // Pick current node from Postorder traversal using postIndex and decrement
    struct Node* tNode = newNode(postorder[(*postIndex)--]);

    if (inStart == inEnd) return tNode;

    // Find the index of this node in Inorder traversal
    int inIndex = search(inorder, inStart, inEnd, tNode->data);

    // Build Right subtree before Left subtree
    tNode->right = buildTree(inorder, postorder, inIndex + 1, inEnd, postIndex);
    tNode->left = buildTree(inorder, postorder, inStart, inIndex - 1, postIndex);

    return tNode;
}

// Function to print preorder traversal
void preorder(struct Node* root, int* first) {
    if (root == NULL) return;
    
    if (!(*first)) printf(" ");
    printf("%d", root->data);
    *first = 0;
    
    preorder(root->left, first);
    preorder(root->right, first);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int in[n], post[n];
    for (int i = 0; i < n; i++) scanf("%d", &in[i]);
    for (int i = 0; i < n; i++) scanf("%d", &post[i]);

    int postIndex = n - 1;
    struct Node* root = buildTree(in, post, 0, n - 1, &postIndex);

    int first = 1;
    preorder(root, &first);
    printf("\n");

    return 0;
}