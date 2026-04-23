/* Problem Statement:
Construct a binary tree from given preorder and inorder traversal arrays.

Input Format:
- First line contains integer N
- Second line contains preorder traversal
- Third line contains inorder traversal

Output Format:
- Print postorder traversal of constructed tree

Example:
Input:
5
1 2 4 5 3
4 2 5 1 3

Output:
4 5 2 3 1

Explanation:
Preorder identifies root, inorder splits left and right subtrees.
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

// Helper function to find the index of a value in the inorder array
int search(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) return i;
    }
    return -1;
}

// Recursive function to build the tree
struct Node* buildTree(int preorder[], int inorder[], int inStart, int inEnd, int* preIndex) {
    if (inStart > inEnd) return NULL;

    // Pick current node from Preorder traversal using preIndex and increment it
    struct Node* tNode = newNode(preorder[(*preIndex)++]);

    // If this node has no children then return
    if (inStart == inEnd) return tNode;

    // Else find the index of this node in Inorder traversal
    int inIndex = search(inorder, inStart, inEnd, tNode->data);

    // Using index in Inorder traversal, construct left and right subtrees
    tNode->left = buildTree(preorder, inorder, inStart, inIndex - 1, preIndex);
    tNode->right = buildTree(preorder, inorder, inIndex + 1, inEnd, preIndex);

    return tNode;
}

// Function to print postorder traversal
void postorder(struct Node* root, int* first) {
    if (root == NULL) return;
    postorder(root->left, first);
    postorder(root->right, first);
    
    if (!(*first)) printf(" ");
    printf("%d", root->data);
    *first = 0;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int pre[n], in[n];
    for (int i = 0; i < n; i++) scanf("%d", &pre[i]);
    for (int i = 0; i < n; i++) scanf("%d", &in[i]);

    int preIndex = 0;
    struct Node* root = buildTree(pre, in, 0, n - 1, &preIndex);

    int first = 1;
    postorder(root, &first);
    printf("\n");

    return 0;
}