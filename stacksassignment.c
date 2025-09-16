#include <stdio.h>
#include <stdlib.h>

// Structure to define a node in the stack
typedef struct Node {
    char data;
    struct Node* prev;
    struct Node* next;
} Node;

// Stack structure using a doubly linked list
typedef struct {
    Node* top; // Points to the top element
} Stack;

// Function to initialize the stack
void initStack(Stack* stack) {
    stack->top = NULL;
}

// Function to push an element onto the stack
void push(Stack* stack, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    newNode->prev = NULL;
    if (stack->top != NULL)
        stack->top->prev = newNode;
    stack->top = newNode;
}

// Function to pop an element from the stack
char pop(Stack* stack) {
    if (stack->top == NULL)
        return '\0'; // Return null character if stack is empty
    Node* temp = stack->top;
    char data = temp->data;
    stack->top = stack->top->next;
    if (stack->top != NULL)
        stack->top->prev = NULL;
    free(temp);
    return data;
}

// Function to check if stack is empty
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Function to check if the brackets are balanced
int isBalanced(const char* expression) {
    Stack stack;
    initStack(&stack);
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&stack, ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&stack))
                return 0;
            char topChar = pop(&stack);
            if ((ch == ')' && topChar != '(') ||
                (ch == '}' && topChar != '{') ||
                (ch == ']' && topChar != '[')) {
                return 0;
            }
        }
    }
    
    int balanced = isEmpty(&stack);
    while (!isEmpty(&stack)) pop(&stack); // Clear remaining elements
    return balanced;
}

// Function to print brackets in FIFO order
void printExpressionFIFO(const char* expression) {
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[' ||
            expression[i] == ')' || expression[i] == '}' || expression[i] == ']') {
            printf("%c ", expression[i]);
        }
    }
    printf("\n");
}

// Function to print brackets in LIFO order
void printExpressionLIFO(const char* expression) {
    Stack stack;
    initStack(&stack);
    
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[' ||
            expression[i] == ')' || expression[i] == '}' || expression[i] == ']') {
            push(&stack, expression[i]);
        }
    }
    
    while (!isEmpty(&stack)) {
        printf("%c ", pop(&stack));
    }
    printf("\n");
}
