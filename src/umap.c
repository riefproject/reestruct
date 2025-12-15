#include "umap.h"
#include <stdio.h>

#define UMAP_DEFAULT_CAPACITY 16

UMap* createUMap(HashFunc hash, HashEquals equals) {
    HashTable* table = createHashTable(UMAP_DEFAULT_CAPACITY, hash, equals);
    if (table == NULL) return NULL;
    UMap* map = new(UMap);
    if (map == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for UMap\n");
        freeHashTable(table);
        return NULL;
    }
    map->table = table;
    return map;
}

bool umapPut(UMap* map, void* key, void* value) {
    if (map == NULL) {
        fprintf(stderr, "Error: UMap is NULL\n");
        return false;
    }
    return htPut(map->table, key, value);
}

void* umapGet(UMap* map, const void* key) {
    if (map == NULL) {
        fprintf(stderr, "Error: UMap is NULL\n");
        return NULL;
    }
    return htGet(map->table, key);
}

bool umapContains(UMap* map, const void* key) {
    if (map == NULL) {
        fprintf(stderr, "Error: UMap is NULL\n");
        return false;
    }
    return htContains(map->table, key);
}

void* umapRemove(UMap* map, const void* key) {
    if (map == NULL) {
        fprintf(stderr, "Error: UMap is NULL\n");
        return NULL;
    }
    return htRemove(map->table, key);
}

size_t umapSize(UMap* map) {
    if (map == NULL) return 0;
    return htSize(map->table);
}

bool umapIsEmpty(UMap* map) {
    if (map == NULL) return true;
    return htIsEmpty(map->table);
}

void clearUMap(UMap* map) {
    if (map == NULL) {
        fprintf(stderr, "Error: UMap is NULL\n");
        return;
    }
    htClear(map->table);
}

void freeUMap(UMap* map) {
    if (map == NULL) return;
    freeHashTable(map->table);
    delete(map);
}

