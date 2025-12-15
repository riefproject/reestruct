#include "map.h"
#include <stdio.h>

static MapEntry* createEntry(void* key, void* value) {
    MapEntry* entry = new(MapEntry);
    if (entry == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for MapEntry\n");
        return NULL;
    }
    entry->key = key;
    entry->value = value;
    entry->left = entry->right = entry->parent = NULL;
    return entry;
}

Map* createMap(MapCompare cmp) {
    if (cmp == NULL) {
        fprintf(stderr, "Error: Comparator must not be NULL\n");
        return NULL;
    }
    Map* map = new(Map);
    if (map == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Map\n");
        return NULL;
    }
    map->root = NULL;
    map->size = 0;
    map->cmp = cmp;
    return map;
}

static MapEntry* findEntry(Map* map, const void* key) {
    MapEntry* current = map->root;
    while (current != NULL) {
        int cmpResult = map->cmp(key, current->key);
        if (cmpResult == 0) return current;
        current = (cmpResult < 0) ? current->left : current->right;
    }
    return NULL;
}

bool mapPut(Map* map, void* key, void* value) {
    if (map == NULL) {
        fprintf(stderr, "Error: Map is NULL\n");
        return false;
    }
    if (map->root == NULL) {
        map->root = createEntry(key, value);
        if (map->root == NULL) return false;
        map->size = 1;
        return true;
    }

    MapEntry* current = map->root;
    while (current != NULL) {
        int cmpResult = map->cmp(key, current->key);
        if (cmpResult == 0) {
            current->value = value;
            return false;  // Updated existing key
        } else if (cmpResult < 0) {
            if (current->left == NULL) {
                current->left = createEntry(key, value);
                if (current->left == NULL) return false;
                current->left->parent = current;
                map->size++;
                return true;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = createEntry(key, value);
                if (current->right == NULL) return false;
                current->right->parent = current;
                map->size++;
                return true;
            }
            current = current->right;
        }
    }
    return false;
}

void* mapGet(Map* map, const void* key) {
    if (map == NULL) {
        fprintf(stderr, "Error: Map is NULL\n");
        return NULL;
    }
    MapEntry* entry = findEntry(map, key);
    return entry ? entry->value : NULL;
}

bool mapContains(Map* map, const void* key) {
    if (map == NULL) {
        fprintf(stderr, "Error: Map is NULL\n");
        return false;
    }
    return findEntry(map, key) != NULL;
}

static MapEntry* minimumEntry(MapEntry* node) {
    if (node == NULL) return NULL;
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

static void transplant(Map* map, MapEntry* u, MapEntry* v) {
    if (u->parent == NULL) {
        map->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

void* mapRemove(Map* map, const void* key) {
    if (map == NULL) {
        fprintf(stderr, "Error: Map is NULL\n");
        return NULL;
    }
    MapEntry* target = findEntry(map, key);
    if (target == NULL) return NULL;

    void* removedValue = target->value;
    if (target->left == NULL) {
        transplant(map, target, target->right);
    } else if (target->right == NULL) {
        transplant(map, target, target->left);
    } else {
        MapEntry* successor = minimumEntry(target->right);
        if (successor->parent != target) {
            transplant(map, successor, successor->right);
            successor->right = target->right;
            if (successor->right != NULL) successor->right->parent = successor;
        }
        transplant(map, target, successor);
        successor->left = target->left;
        if (successor->left != NULL) successor->left->parent = successor;
    }
    delete(target);
    map->size--;
    return removedValue;
}

size_t mapSize(Map* map) {
    if (map == NULL) return 0;
    return map->size;
}

bool mapIsEmpty(Map* map) {
    if (map == NULL) return true;
    return map->size == 0;
}

static void traverseInOrder(MapEntry* node, void (*visit)(void* key, void* value)) {
    if (node == NULL) return;
    traverseInOrder(node->left, visit);
    visit(node->key, node->value);
    traverseInOrder(node->right, visit);
}

void mapTraverseInOrder(Map* map, void (*visit)(void* key, void* value)) {
    if (map == NULL) {
        fprintf(stderr, "Error: Map is NULL\n");
        return;
    }
    if (visit == NULL) return;
    traverseInOrder(map->root, visit);
}

static void freeEntries(MapEntry* node) {
    if (node == NULL) return;
    freeEntries(node->left);
    freeEntries(node->right);
    delete(node);
}

void clearMap(Map* map) {
    if (map == NULL) {
        fprintf(stderr, "Error: Map is NULL\n");
        return;
    }
    freeEntries(map->root);
    map->root = NULL;
    map->size = 0;
}

void freeMap(Map* map) {
    if (map == NULL) return;
    clearMap(map);
    delete(map);
}

