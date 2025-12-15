#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*      CONSTRUCTOR
 * ==================== */
Stack* createStack(void) {
    Stack* stack = new(Stack);
    if (stack == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Stack\n");
        return NULL;
    }
    stack->Top = NULL;
    stack->size = 0;
    return stack;
}


/*      STATUS CHECKS
 * ==================== */
bool isStackEmpty(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Stack is NULL\n");
        return true;
    }
    return (stack->Top == NULL);
}

bool isStackFull(Stack* stack) {
    (void)stack;
    return false;  // Linked implementation is effectively unbounded.
}

uint getStackSize(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Stack is NULL\n");
        return 0;
    }
    return stack->size;
}


/*     STACK OPERATIONS
 * ==================== */
void push(Stack* stack, void* data) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Stack is NULL\n");
        return;
    }

    SLLNode* newNode = createSLLNode(data);
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new node\n");
        return;
    }

    newNode->next = stack->Top;
    stack->Top = newNode;
    stack->size++;
}

void* pop(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Stack is NULL\n");
        return NULL;
    }
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Error: Stack is empty\n");
        return NULL;
    }

    SLLNode* topNode = stack->Top;
    void* data = topNode->data;
    stack->Top = topNode->next;
    delete(topNode);
    stack->size--;

    return data;
}

void* Stack_Peek(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Stack is NULL\n");
        return NULL;
    }
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Error: Stack is empty\n");
        return NULL;
    }
    return stack->Top->data;
}


/*  DEALOC AND DESTRUCT
 * ==================== */
void clearStack(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Stack is NULL\n");
        return;
    }

    while (!isStackEmpty(stack)) {
        pop(stack);
    }
}

void freeStack(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Stack is NULL\n");
        return;
    }
    clearStack(stack);
    delete(stack);
}


/*      PRINT STACK
 * ==================== */
void printStack(Stack* stack, void (*printFunc)(void*)) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Stack is NULL\n");
        return;
    }
    SLLNode* current = stack->Top;
    while (current != NULL) {
        printFunc(current->data);
        current = current->next;
    }
    printf("\n");
}

static void printStackReverseRecursive(SLLNode* node, void (*printFunc)(void*)) {
    if (node == NULL) return;
    printStackReverseRecursive(node->next, printFunc);
    printFunc(node->data);
}

void printStackReverse(Stack* stack, void (*printFunc)(void*)) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Stack is NULL\n");
        return;
    }
    printStackReverseRecursive(stack->Top, printFunc);
    printf("\n");
}
