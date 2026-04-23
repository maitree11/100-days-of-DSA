/* Problem Statement:
Given a binary tree, print its vertical order traversal. Nodes that lie on the same vertical line should be printed together from top to bottom and from left to right.

Input Format:
- First line contains integer N (number of nodes)
- Second line contains N space-separated integers representing level-order traversal (-1 indicates NULL)

Output Format:
- Print nodes column by column from leftmost to rightmost vertical line

Example:
Input:
7
1 2 3 4 5 6 7

Output:
4
2
1 5 6
3
7

Explanation:
Vertical lines are formed based on horizontal distance from root. Nodes sharing the same distance are printed together.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Structure to store node and its HD for queue
struct QueueNode {
    struct Node* tNode;
    int hd;
};

struct Node* newNode(int val) {
    if (val == -1) return NULL;
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

// Level-order tree construction
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

// Vertical Order Logic
void verticalOrder(struct Node* root, int n) {
    if (!root) return;

    // Use a large offset to handle negative HDs
    int offset = n; 
    // Array of linked lists to store nodes for each HD
    struct List { int val; struct List* next; };
    struct List* columns[2 * n + 1];
    struct List* tails[2 * n + 1];
    for (int i = 0; i < 2 * n + 1; i++) columns[i] = tails[i] = NULL;

    struct QueueNode* q = (struct QueueNode*)malloc(sizeof(struct QueueNode) * n);
    int front = 0, rear = 0;
    int min_hd = 0, max_hd = 0;

    q[rear++] = (struct QueueNode){root, 0};

    while (front < rear) {
        struct QueueNode curr = q[front++];
        int hd = curr.hd;
        if (hd < min_hd) min_hd = hd;
        if (hd > max_hd) max_hd = hd;

        // Add to linked list at columns[hd + offset]
        struct List* newEntry = (struct List*)malloc(sizeof(struct List));
        newEntry->val = curr.tNode->data;
        newEntry->next = NULL;
        if (!columns[hd + offset]) columns[hd + offset] = tails[hd + offset] = newEntry;
        else { tails[hd + offset]->next = newEntry; tails[hd + offset] = newEntry; }

        if (curr.tNode->left) q[rear++] = (struct QueueNode){curr.tNode->left, hd - 1};
        if (curr.tNode->right) q[rear++] = (struct QueueNode){curr.tNode->right, hd + 1};
    }

    // Print from min_hd to max_hd
    for (int i = min_hd; i <= max_hd; i++) {
        struct List* temp = columns[i + offset];
        while (temp) {
            printf("%d%s", temp->val, temp->next ? " " : "");
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    struct Node* root = buildTree(arr, n);
    verticalOrder(root, n);

    return 0;
}