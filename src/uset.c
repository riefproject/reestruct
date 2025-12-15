#include "uset.h"
#include <stdio.h>

#define USET_DEFAULT_CAPACITY 16

USet* createUSet(HashFunc hash, HashEquals equals) {
    HashTable* table = createHashTable(USET_DEFAULT_CAPACITY, hash, equals);
    if (table == NULL) return NULL;
    USet* set = new(USet);
    if (set == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for USet\n");
        freeHashTable(table);
        return NULL;
    }
    set->table = table;
    return set;
}

bool usetAdd(USet* set, void* key) {
    if (set == NULL) {
        fprintf(stderr, "Error: USet is NULL\n");
        return false;
    }
    return htPut(set->table, key, key);
}

bool usetContains(USet* set, const void* key) {
    if (set == NULL) {
        fprintf(stderr, "Error: USet is NULL\n");
        return false;
    }
    return htContains(set->table, key);
}

bool usetRemove(USet* set, const void* key) {
    if (set == NULL) {
        fprintf(stderr, "Error: USet is NULL\n");
        return false;
    }
    if (!htContains(set->table, key)) return false;
    htRemove(set->table, key);
    return true;
}

size_t usetSize(USet* set) {
    if (set == NULL) return 0;
    return htSize(set->table);
}

bool usetIsEmpty(USet* set) {
    if (set == NULL) return true;
    return htIsEmpty(set->table);
}

void clearUSet(USet* set) {
    if (set == NULL) {
        fprintf(stderr, "Error: USet is NULL\n");
        return;
    }
    htClear(set->table);
}

void freeUSet(USet* set) {
    if (set == NULL) return;
    freeHashTable(set->table);
    delete(set);
}

