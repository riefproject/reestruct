#include "hashtable.h"
#include <stdio.h>

#define LOAD_FACTOR_NUM 3
#define LOAD_FACTOR_DEN 4
#define MIN_CAPACITY 16

static bool defaultEquals(const void* a, const void* b) {
    return a == b;
}

static size_t clampCapacity(size_t capacity) {
    if (capacity < MIN_CAPACITY) return MIN_CAPACITY;
    return capacity;
}

static size_t bucketIndex(const HashTable* table, const void* key) {
    size_t hashValue = table->hash(key);
    return hashValue % table->capacity;
}

static void rehash(HashTable* table) {
    size_t newCapacity = table->capacity * 2;
    HTEntry** newBuckets = (HTEntry**)calloc(newCapacity, sizeof(HTEntry*));
    if (newBuckets == NULL) {
        fprintf(stderr, "Error: Memory allocation failed during rehash\n");
        return;
    }

    for (size_t i = 0; i < table->capacity; i++) {
        HTEntry* entry = table->buckets[i];
        while (entry != NULL) {
            HTEntry* next = entry->next;
            size_t newIndex = table->hash(entry->key) % newCapacity;
            entry->next = newBuckets[newIndex];
            newBuckets[newIndex] = entry;
            entry = next;
        }
    }

    free(table->buckets);
    table->buckets = newBuckets;
    table->capacity = newCapacity;
}

HashTable* createHashTable(size_t capacity, HashFunc hash, HashEquals equals) {
    if (hash == NULL) {
        fprintf(stderr, "Error: Hash function must not be NULL\n");
        return NULL;
    }
    HashTable* table = new(HashTable);
    if (table == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for HashTable\n");
        return NULL;
    }
    table->capacity = clampCapacity(capacity);
    table->size = 0;
    table->hash = hash;
    table->equals = equals ? equals : defaultEquals;
    table->buckets = (HTEntry**)calloc(table->capacity, sizeof(HTEntry*));
    if (table->buckets == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for buckets\n");
        delete(table);
        return NULL;
    }
    return table;
}

bool htPut(HashTable* table, void* key, void* value) {
    if (table == NULL) {
        fprintf(stderr, "Error: HashTable is NULL\n");
        return false;
    }
    size_t index = bucketIndex(table, key);
    HTEntry* current = table->buckets[index];
    while (current != NULL) {
        if (table->equals(current->key, key)) {
            current->value = value;
            return false;  // Updated existing key
        }
        current = current->next;
    }

    HTEntry* entry = new(HTEntry);
    if (entry == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for hash entry\n");
        return false;
    }
    entry->key = key;
    entry->value = value;
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->size++;

    if (table->size * LOAD_FACTOR_DEN >= table->capacity * LOAD_FACTOR_NUM) {
        rehash(table);
    }
    return true;
}

void* htGet(HashTable* table, const void* key) {
    if (table == NULL) {
        fprintf(stderr, "Error: HashTable is NULL\n");
        return NULL;
    }
    size_t index = bucketIndex(table, key);
    HTEntry* current = table->buckets[index];
    while (current != NULL) {
        if (table->equals(current->key, key)) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

bool htContains(HashTable* table, const void* key) {
    if (table == NULL) {
        fprintf(stderr, "Error: HashTable is NULL\n");
        return false;
    }
    size_t index = bucketIndex(table, key);
    HTEntry* current = table->buckets[index];
    while (current != NULL) {
        if (table->equals(current->key, key)) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void* htRemove(HashTable* table, const void* key) {
    if (table == NULL) {
        fprintf(stderr, "Error: HashTable is NULL\n");
        return NULL;
    }
    size_t index = bucketIndex(table, key);
    HTEntry* current = table->buckets[index];
    HTEntry* prev = NULL;
    while (current != NULL) {
        if (table->equals(current->key, key)) {
            if (prev == NULL) {
                table->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            void* value = current->value;
            delete(current);
            table->size--;
            return value;
        }
        prev = current;
        current = current->next;
    }
    return NULL;
}

size_t htSize(HashTable* table) {
    if (table == NULL) return 0;
    return table->size;
}

bool htIsEmpty(HashTable* table) {
    if (table == NULL) return true;
    return table->size == 0;
}

void htClear(HashTable* table) {
    if (table == NULL) {
        fprintf(stderr, "Error: HashTable is NULL\n");
        return;
    }
    for (size_t i = 0; i < table->capacity; i++) {
        HTEntry* current = table->buckets[i];
        while (current != NULL) {
            HTEntry* next = current->next;
            delete(current);
            current = next;
        }
        table->buckets[i] = NULL;
    }
    table->size = 0;
}

void freeHashTable(HashTable* table) {
    if (table == NULL) return;
    htClear(table);
    free(table->buckets);
    delete(table);
}
