/* Problem: Implement a stack data structure using an array with the following operations: push, pop, and display.

Input:
- First line: integer n (number of operations)
- Next n lines: operation type and value (if applicable)
  - 1 value: push value
  - 2: pop
  - 3: display

Output:
- For display: print stack elements from top to bottom
- For pop: print popped element or 'Stack Underflow'

Example:
Input:
5
1 10
1 20
3
2
3

Output:
20 10
20
10
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000 // Define maximum capacity of the stack

int stack[MAX];
int top = -1; // -1 indicates the stack is empty

// Function to add an element to the top
void push(int value) {
    if (top >= MAX - 1) {
        // In a real scenario, you'd handle Stack Overflow here
        return;
    }
    stack[++top] = value;
}

// Function to remove and return the top element
void pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
    } else {
        printf("%d\n", stack[top--]);
    }
}

// Function to print all elements from top to bottom
void display() {
    if (top == -1) {
        return;
    }
    for (int i = top; i >= 0; i--) {
        printf("%d%s", stack[i], (i == 0) ? "" : " ");
    }
    printf("\n");
}

int main() {
    int n, choice, value;

    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &choice);

        if (choice == 1) {
            scanf("%d", &value);
            push(value);
        } else if (choice == 2) {
            pop();
        } else if (choice == 3) {
            display();
        }
    }

    return 0;
}