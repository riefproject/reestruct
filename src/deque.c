#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>

// ===================================================
//                . . . DEQUE . . .
// ===================================================

/*      CONSTRUCTOR
 * ==================== */
Deque* createDeque(void) {
    Deque* queue = new(Deque);
    if (queue == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Deque\n");
        return NULL;
    }
    queue->Front = NULL;
    queue->Rear = NULL;
    queue->size = 0;
    return queue;
}


/*      STATUS CHECKS
 * ==================== */
bool isDequeEmpty(Deque* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return true;
    }
    return (queue->Front == NULL && queue->Rear == NULL);
}

uint getDequeSize(Deque* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return 0;
    }
    return queue->size;
}


/*     ELEMENT ACCESS
 * ==================== */
void* Deque_peekFront(Deque* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return NULL;
    }
    if (isDequeEmpty(queue)) {
        fprintf(stderr, "Error: Deque is empty\n");
        return NULL;
    }
    return queue->Front->data;
}

void* Deque_peekBack(Deque* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return NULL;
    }
    if (isDequeEmpty(queue)) {
        fprintf(stderr, "Error: Deque is empty\n");
        return NULL;
    }
    return queue->Rear->data;
}


/*     DEQUE OPERATIONS
 * ==================== */
void pushBack(Deque* queue, void* data) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return;
    }
    SLLNode* newNode = createSLLNode(data);
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new node\n");
        return;
    }
    if (isDequeEmpty(queue)) {
        queue->Front = newNode;
        queue->Rear = newNode;
    }
    else {
        queue->Rear->next = newNode;
        queue->Rear = newNode;
    }
    queue->size++;
    newNode->next = NULL;
}

void pushFront(Deque* queue, void* data) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return;
    }
    SLLNode* newNode = createSLLNode(data);
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new node\n");
        return;
    }
    if (isDequeEmpty(queue)) {
        queue->Front = newNode;
        queue->Rear = newNode;
    }
    else {
        newNode->next = queue->Front;
        queue->Front = newNode;
    }
    queue->size++;
}

void* popBack(Deque* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return NULL;
    }
    if (isDequeEmpty(queue)) {
        fprintf(stderr, "Error: Deque is empty\n");
        return NULL;
    }
    SLLNode* rearNode = queue->Rear;
    void* data = rearNode->data;
    if (queue->Front == queue->Rear) {
        queue->Front = NULL;
        queue->Rear = NULL;
    }
    else {
        SLLNode* current = queue->Front;
        while (current->next != queue->Rear) {
            current = current->next;
        }
        current->next = NULL;
        queue->Rear = current;
    }
    delete(rearNode);
    queue->size--;
    return data;
}

void* popFront(Deque* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return NULL;
    }
    if (isDequeEmpty(queue)) {
        fprintf(stderr, "Error: Deque is empty\n");
        return NULL;
    }
    SLLNode* frontNode = queue->Front;
    void* data = frontNode->data;
    queue->Front = frontNode->next;
    if (queue->Front == NULL) {
        queue->Rear = NULL;
    }
    delete(frontNode);
    queue->size--;
    return data;
}


/*  DEALOC AND DESTRUCT
 * ==================== */
void clearDeque(Deque* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return;
    }
    while (!isDequeEmpty(queue)) {
        popFront(queue);
    }
    queue->Front = NULL;
    queue->Rear = NULL;
    queue->size = 0;
}

void freeDeque(Deque* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return;
    }
    clearDeque(queue);
    delete(queue);
}


/*      PRINT QUEUE
 * ==================== */
void printDeque(Deque* queue, void (*printFunc)(void*)) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return;
    }
    SLLNode* current = queue->Front;
    while (current != NULL) {
        printFunc(current->data);
        current = current->next;
    }
}

void printDequeReverse(Deque* queue, void (*printFunc)(void*)) {
    // This function is not implemented in the original code.
    // You can implement it using a stack or recursion.
    if (queue == NULL) {
        fprintf(stderr, "Error: Deque is NULL\n");
        return;
    }
}
