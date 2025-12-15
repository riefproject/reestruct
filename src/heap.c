#include "heap.h"
#include <stdio.h>

#define DEFAULT_HEAP_CAPACITY 16

static void swap(void** a, void** b) {
    void* tmp = *a;
    *a = *b;
    *b = tmp;
}

static bool ensureCapacity(Heap* heap) {
    if (heap->size < heap->capacity) return true;
    size_t newCapacity = heap->capacity * 2;
    void** resized = (void**)realloc(heap->data, newCapacity * sizeof(void*));
    if (resized == NULL) {
        fprintf(stderr, "Error: Memory allocation failed while growing heap\n");
        return false;
    }
    heap->data = resized;
    heap->capacity = newCapacity;
    return true;
}

static void siftUp(Heap* heap, size_t idx) {
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (heap->cmp(heap->data[idx], heap->data[parent]) >= 0) break;
        swap(&heap->data[idx], &heap->data[parent]);
        idx = parent;
    }
}

static void siftDown(Heap* heap, size_t idx) {
    while (true) {
        size_t left = idx * 2 + 1;
        size_t right = idx * 2 + 2;
        size_t smallest = idx;

        if (left < heap->size && heap->cmp(heap->data[left], heap->data[smallest]) < 0) {
            smallest = left;
        }
        if (right < heap->size && heap->cmp(heap->data[right], heap->data[smallest]) < 0) {
            smallest = right;
        }
        if (smallest == idx) break;
        swap(&heap->data[idx], &heap->data[smallest]);
        idx = smallest;
    }
}

Heap* createHeapWithCapacity(HeapCompare cmp, size_t capacity) {
    if (cmp == NULL) {
        fprintf(stderr, "Error: Comparator must not be NULL\n");
        return NULL;
    }
    Heap* heap = new(Heap);
    if (heap == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Heap\n");
        return NULL;
    }
    heap->capacity = capacity < DEFAULT_HEAP_CAPACITY ? DEFAULT_HEAP_CAPACITY : capacity;
    heap->size = 0;
    heap->cmp = cmp;
    heap->data = (void**)malloc(heap->capacity * sizeof(void*));
    if (heap->data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Heap storage\n");
        delete(heap);
        return NULL;
    }
    return heap;
}

Heap* createHeap(HeapCompare cmp) {
    return createHeapWithCapacity(cmp, DEFAULT_HEAP_CAPACITY);
}

bool heapIsEmpty(Heap* heap) {
    if (heap == NULL) {
        fprintf(stderr, "Error: Heap is NULL\n");
        return true;
    }
    return heap->size == 0;
}

size_t heapSize(Heap* heap) {
    if (heap == NULL) {
        fprintf(stderr, "Error: Heap is NULL\n");
        return 0;
    }
    return heap->size;
}

bool heapPush(Heap* heap, void* item) {
    if (heap == NULL) {
        fprintf(stderr, "Error: Heap is NULL\n");
        return false;
    }
    if (!ensureCapacity(heap)) return false;
    heap->data[heap->size] = item;
    siftUp(heap, heap->size);
    heap->size++;
    return true;
}

void* heapPop(Heap* heap) {
    if (heap == NULL) {
        fprintf(stderr, "Error: Heap is NULL\n");
        return NULL;
    }
    if (heapIsEmpty(heap)) {
        fprintf(stderr, "Error: Heap is empty\n");
        return NULL;
    }
    void* top = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        siftDown(heap, 0);
    }
    return top;
}

void* heapPeek(Heap* heap) {
    if (heap == NULL) {
        fprintf(stderr, "Error: Heap is NULL\n");
        return NULL;
    }
    if (heapIsEmpty(heap)) {
        fprintf(stderr, "Error: Heap is empty\n");
        return NULL;
    }
    return heap->data[0];
}

void clearHeap(Heap* heap) {
    if (heap == NULL) {
        fprintf(stderr, "Error: Heap is NULL\n");
        return;
    }
    heap->size = 0;
}

void freeHeap(Heap* heap) {
    if (heap == NULL) return;
    free(heap->data);
    delete(heap);
}

