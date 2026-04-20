/* Problem: Evaluate Postfix Expression - Implement using linked list with dynamic memory allocation.

Input:
- Postfix expression with operands and operators

Output:
- Print the integer result

Example:
Input:
2 3 1 * + 9 -

Output:
-4

Explanation:
Use stack to store operands, apply operators by popping operands, push result back. Final stack top is result.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Node structure for the stack
struct Node {
    int data;
    struct Node* next;
};

// Push operation for the stack
void push(struct Node** top, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = *top;
    *top = newNode;
}

// Pop operation for the stack
int pop(struct Node** top) {
    if (*top == NULL) return 0;
    struct Node* temp = *top;
    int val = temp->data;
    *top = (*top)->next;
    free(temp);
    return val;
}

int evaluatePostfix(char* exp) {
    struct Node* stack = NULL;

    for (int i = 0; exp[i] != '\0'; i++) {
        // Skip spaces
        if (exp[i] == ' ') continue;

        // If the character is a digit, handle multi-digit numbers
        if (isdigit(exp[i])) {
            int num = 0;
            while (isdigit(exp[i])) {
                num = num * 10 + (exp[i] - '0');
                i++;
            }
            i--; // Adjust index for the outer loop
            push(&stack, num);
        } 
        // If the character is an operator
        else {
            int val2 = pop(&stack); // Second operand
            int val1 = pop(&stack); // First operand

            switch (exp[i]) {
                case '+': push(&stack, val1 + val2); break;
                case '-': push(&stack, val1 - val2); break;
                case '*': push(&stack, val1 * val2); break;
                case '/': push(&stack, val1 / val2); break;
            }
        }
    }
    return pop(&stack);
}

int main() {
    char exp[100];
    // Read the entire line including spaces
    scanf("%[^\n]s", exp);

    printf("%d\n", evaluatePostfix(exp));

    return 0;
}