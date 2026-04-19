/* Problem: Convert an infix expression to postfix notation using stack.

Input:
- Single line: infix expression (operands are single characters)

Output:
- Print the postfix expression

Example:
Input:
A+B*C

Output:
ABC*+

Explanation:
Operator precedence: * > +
Use stack to handle operator precedence and associativity
*/

#include <stdio.h>
#include <ctype.h> // for isalnum()
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char x) {
    stack[++top] = x;
}

char pop() {
    if (top == -1) return -1;
    return stack[top--];
}

// Function to return precedence of operators
int precedence(char x) {
    if (x == '(') return 0;
    if (x == '+' || x == '-') return 1;
    if (x == '*' || x == '/') return 2;
    if (x == '^') return 3;
    return 0;
}

int main() {
    char infix[MAX], x;
    scanf("%s", infix);
    
    for (int i = 0; infix[i] != '\0'; i++) {
        // 1. If character is an operand, print it
        if (isalnum(infix[i])) {
            printf("%c", infix[i]);
        }
        // 2. If it's a '(', push to stack
        else if (infix[i] == '(') {
            push('(');
        }
        // 3. If it's a ')', pop until '(' is found
        else if (infix[i] == ')') {
            while ((x = pop()) != '(') {
                printf("%c", x);
            }
        }
        // 4. If it's an operator
        else {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                printf("%c", pop());
            }
            push(infix[i]);
        }
    }

    // 5. Pop all remaining operators from stack
    while (top != -1) {
        printf("%c", pop());
    }
    printf("\n");

    return 0;
}