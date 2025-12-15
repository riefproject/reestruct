#include "set.h"
#include <stdio.h>

Set* createSet(MapCompare cmp) {
    Map* map = createMap(cmp);
    if (map == NULL) return NULL;
    Set* set = new(Set);
    if (set == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Set\n");
        freeMap(map);
        return NULL;
    }
    set->map = map;
    return set;
}

bool setAdd(Set* set, void* key) {
    if (set == NULL) {
        fprintf(stderr, "Error: Set is NULL\n");
        return false;
    }
    return mapPut(set->map, key, key);
}

bool setContains(Set* set, const void* key) {
    if (set == NULL) {
        fprintf(stderr, "Error: Set is NULL\n");
        return false;
    }
    return mapContains(set->map, key);
}

bool setRemove(Set* set, const void* key) {
    if (set == NULL) {
        fprintf(stderr, "Error: Set is NULL\n");
        return false;
    }
    if (!mapContains(set->map, key)) return false;
    mapRemove(set->map, key);
    return true;
}

size_t setSize(Set* set) {
    if (set == NULL) return 0;
    return mapSize(set->map);
}

bool setIsEmpty(Set* set) {
    if (set == NULL) return true;
    return mapIsEmpty(set->map);
}

static void traverseAdapter(MapEntry* node, void (*visit)(void*)) {
    if (node == NULL) return;
    traverseAdapter(node->left, visit);
    visit(node->key);
    traverseAdapter(node->right, visit);
}

void setTraverse(Set* set, void (*visit)(void* key)) {
    if (set == NULL) {
        fprintf(stderr, "Error: Set is NULL\n");
        return;
    }
    if (visit == NULL) return;
    traverseAdapter(set->map->root, visit);
}

void clearSet(Set* set) {
    if (set == NULL) {
        fprintf(stderr, "Error: Set is NULL\n");
        return;
    }
    clearMap(set->map);
}

void freeSet(Set* set) {
    if (set == NULL) return;
    freeMap(set->map);
    delete(set);
}
