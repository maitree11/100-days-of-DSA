/* Problem: Polynomial Using Linked List - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n (number of terms)
- Next n lines: two integers (coefficient and exponent)

Output:
- Print polynomial in standard form, e.g., 10x^4 + 20x^3 + 30x^2 + 40x + 50

Example:
Input:
5
10 4
20 3
30 2
40 1
50 0

Output:
10x^4 + 20x^3 + 30x^2 + 40x + 50

Explanation:
Each node stores coefficient and exponent. Traverse nodes to print polynomial in decreasing exponent order.
*/

#include <stdio.h>
#include <stdlib.h>

// Node structure to represent a polynomial term
struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

// Function to create a new term
struct Node* createNode(int c, int e) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = c;
    newNode->exp = e;
    newNode->next = NULL;
    return newNode;
}

void printPolynomial(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        // Print the term
        if (temp->exp == 0) {
            printf("%d", temp->coeff);
        } else if (temp->exp == 1) {
            printf("%dx", temp->coeff);
        } else {
            printf("%dx^%d", temp->coeff, temp->exp);
        }

        // Move to next node
        temp = temp->next;

        // Print " + " only if there is a next term
        if (temp != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

int main() {
    int n, c, e;
    struct Node *head = NULL, *tail = NULL;

    // 1. Read number of terms
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    // 2. Build the linked list
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &c, &e);
        struct Node* newNode = createNode(c, e);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // 3. Print the result
    printPolynomial(head);

    return 0;
}