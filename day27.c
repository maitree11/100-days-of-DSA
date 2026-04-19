/* Problem: Find Intersection Point of Two Linked Lists - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers (first list)
- Third line: integer m
- Fourth line: m space-separated integers (second list)

Output:
- Print value of intersection node or 'No Intersection'

Example:
Input:
5
10 20 30 40 50
4
15 25 30 40 50

Output:
30

Explanation:
Calculate lengths, advance pointer in longer list, traverse both simultaneously. First common node is intersection.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Helper to build list (Fixed to handle the input quirk)
struct Node* buildList(int n) {
    if (n <= 0) return NULL;
    struct Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = val;
        newNode->next = NULL;
        if (!head) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }
    return head;
}

int main() {
    int n, m;

    if (scanf("%d", &n) != 1) return 0;
    struct Node* head1 = buildList(n);

    if (scanf("%d", &m) != 1) return 0;
    struct Node* head2 = buildList(m);

    if (!head1 || !head2) {
        printf("No Intersection\n");
        return 0;
    }

    struct Node *a = head1;
    struct Node *b = head2;

    // The logic: Traverse both. When one hits NULL, switch to the other head.
    // They will eventually sync up at the intersection or both hit NULL.
    // We use a counter to prevent infinite loops if there's truly no intersection
    int switchCount = 0;
    while (a != NULL && b != NULL) {
        if (a->data == b->data) {
            printf("%d\n", a->data);
            return 0;
        }
        
        a = a->next;
        b = b->next;

        // If one finishes, swap to the other list's head
        if (a == NULL && switchCount < 2) { a = head2; switchCount++; }
        if (b == NULL && switchCount < 2) { b = head1; switchCount++; }
    }

    printf("No Intersection\n");
    return 0;
}