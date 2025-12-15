#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*      CONSTRUCTOR
 * ==================== */
Queue* createQueue(void) {
    Queue* queue = new(Queue);
    if (queue == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Queue\n");
        return NULL;
    }
    queue->Front = NULL;
    queue->Rear = NULL;
    queue->size = 0;
    return queue;
}


/*      STATUS CHECKS
 * ==================== */
bool isQueueEmpty(Queue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Queue is NULL\n");
        return true;
    }
    return (queue->Front == NULL && queue->Rear == NULL);
}

bool isQueueFull(Queue* queue) {
    (void)queue;
    return false;  // Linked implementation has no fixed capacity.
}

uint getQueueSize(Queue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Queue is NULL\n");
        return 0;
    }
    return queue->size;
}


/*   QUEUE OPERATIONS
 * ==================== */
void Enqueue(Queue* queue, void* data) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Queue is NULL\n");
        return;
    }
    SLLNode* newNode = createSLLNode(data);
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new node\n");
        return;
    }
    if (isQueueEmpty(queue)) {
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

void* Dequeue(Queue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Queue is NULL\n");
        return NULL;
    }
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Error: Queue is empty\n");
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

void* Queue_Peek(Queue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Queue is NULL\n");
        return NULL;
    }
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Error: Queue is empty\n");
        return NULL;
    }
    return queue->Front->data;
}


/*  DEALOC AND DESTRUCT
 * ==================== */
void clearQueue(Queue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Queue is NULL\n");
        return;
    }
    while (!isQueueEmpty(queue)) {
        Dequeue(queue);
    }
    queue->Front = NULL;
    queue->Rear = NULL;
    queue->size = 0;
}

void freeQueue(Queue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Queue is NULL\n");
        return;
    }
    clearQueue(queue);
    delete(queue);
}


/*      PRINT QUEUE
 * ==================== */
void printQueue(Queue* queue, void (*printFunc)(void*)) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Queue is NULL\n");
        return;
    }
    SLLNode* current = queue->Front;
    while (current != NULL) {
        printFunc(current->data);
        current = current->next;
    }
    printf("\n");
}

static void printQueueReverseRecursive(SLLNode* node, void (*printFunc)(void*)) {
    if (node == NULL) return;
    printQueueReverseRecursive(node->next, printFunc);
    printFunc(node->data);
}

void printQueueReverse(Queue* queue, void (*printFunc)(void*)) {
    if (queue == NULL) {
        fprintf(stderr, "Error: Queue is NULL\n");
        return;
    }
    printQueueReverseRecursive(queue->Front, printFunc);
    printf("\n");
}
