#include "reestruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int tests_run = 0;
static int tests_failed = 0;

#define CHECK(cond, msg)                                                             \
    do {                                                                             \
        tests_run++;                                                                 \
        if (!(cond)) {                                                               \
            tests_failed++;                                                          \
            fprintf(stderr, "[FAIL] %s:%d: %s\n", __FILE__, __LINE__, (msg));        \
        }                                                                            \
    } while (0)

static int intCompare(const void* a, const void* b) {
    int da = *(const int*)a;
    int db = *(const int*)b;
    return (da > db) - (da < db);
}

static size_t intHash(const void* key) {
    return (size_t)(*(const int*)key);
}

static bool intEquals(const void* a, const void* b) {
    return *(const int*)a == *(const int*)b;
}

static void test_linked_list(void) {
    SingleLinkedList* list = createSingleLinkedList();
    int a = 1, b = 2, c = 3;

    SLL_insertBack(list, &a);
    SLL_insertFront(list, &b);
    SLL_insertBack(list, &c);

    CHECK(list->size == 3, "SLL size after inserts");
    CHECK(SLL_getFront(list) == &b, "SLL front value");
    CHECK(SLL_getBack(list) == &c, "SLL back value");

    SLL_removeFront(list, list->head);
    CHECK(list->size == 2, "SLL size after remove front");
    CHECK(SLL_getFront(list) == &a, "SLL front after removal");

    SLL_removeBack(list, list->tail);
    CHECK(list->size == 1, "SLL size after remove back");
    CHECK(SLL_getBack(list) == &a, "SLL back after removal");

    SLL_freeList(list);
}

static void test_stack(void) {
    Stack* stack = createStack();
    int a = 10, b = 20;
    push(stack, &a);
    push(stack, &b);
    CHECK(getStackSize(stack) == 2, "stack size after pushes");
    CHECK(Stack_Peek(stack) == &b, "stack peek");
    CHECK(pop(stack) == &b, "stack pop order");
    CHECK(pop(stack) == &a, "stack pop second");
    CHECK(isStackEmpty(stack), "stack empty after pops");
    freeStack(stack);
}

static void test_queue(void) {
    Queue* q = createQueue();
    int a = 5, b = 6;
    Enqueue(q, &a);
    Enqueue(q, &b);
    CHECK(getQueueSize(q) == 2, "queue size after enqueues");
    CHECK(Queue_Peek(q) == &a, "queue peek");
    CHECK(Dequeue(q) == &a, "queue dequeue order");
    CHECK(Dequeue(q) == &b, "queue dequeue second");
    CHECK(isQueueEmpty(q), "queue empty after dequeues");
    freeQueue(q);
}

static void test_deque(void) {
    Deque* d = createDeque();
    int a = 1, b = 2, c = 3;
    pushFront(d, &b);   // deque: b
    pushBack(d, &c);    // deque: b c
    pushFront(d, &a);   // deque: a b c
    CHECK(getDequeSize(d) == 3, "deque size after pushes");
    CHECK(Deque_peekFront(d) == &a, "deque peek front");
    CHECK(Deque_peekBack(d) == &c, "deque peek back");
    CHECK(popFront(d) == &a, "deque pop front");
    CHECK(popBack(d) == &c, "deque pop back");
    CHECK(getDequeSize(d) == 1, "deque size after pops");
    freeDeque(d);
}

static int bt_collect[8];
static size_t bt_idx = 0;
static void bt_visit(void* data) {
    if (bt_idx < sizeof(bt_collect) / sizeof(bt_collect[0])) {
        bt_collect[bt_idx++] = *(int*)data;
    }
}

static void test_binary_tree(void) {
    int rootVal = 2, leftVal = 1, rightVal = 3;
    BinaryTree* tree = createBinaryTree(&rootVal);
    insertLeft(tree, tree->root, &leftVal);
    insertRight(tree, tree->root, &rightVal);
    bt_idx = 0;
    inorderTraversal(tree, bt_visit);
    CHECK(bt_idx == 3, "binary tree traversal count");
    CHECK(bt_collect[0] == 1 && bt_collect[1] == 2 && bt_collect[2] == 3, "binary tree inorder sequence");
    CHECK(getBinaryTreeDepth(tree) == 2, "binary tree depth");

    removeNode(tree, tree->root->left);
    bt_idx = 0;
    inorderTraversal(tree, bt_visit);
    CHECK(bt_idx == 2, "binary tree traversal after remove");
    CHECK(bt_collect[0] == 2 && bt_collect[1] == 3, "binary tree inorder after remove");
    destroyBinaryTree(tree);
}

static void test_heap(void) {
    Heap* heap = createHeap(intCompare);
    int vals[] = {7, 3, 9, 1};
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); i++) {
        heapPush(heap, &vals[i]);
    }
    CHECK(heapSize(heap) == 4, "heap size after pushes");
    CHECK(*(int*)heapPeek(heap) == 1, "heap peek min");
    int last = -1;
    while (!heapIsEmpty(heap)) {
        int current = *(int*)heapPop(heap);
        CHECK(last <= current, "heap pop order non-decreasing");
        last = current;
    }
    CHECK(heapIsEmpty(heap), "heap empty after pops");
    freeHeap(heap);
}

static int map_order[8];
static size_t map_idx = 0;
static void map_visit(void* key, void* value) {
    (void)value;
    if (map_idx < sizeof(map_order) / sizeof(map_order[0])) {
        map_order[map_idx++] = *(int*)key;
    }
}

static void test_map_set(void) {
    Map* map = createMap(intCompare);
    int k1 = 3, k2 = 1, k3 = 2;
    const char* v1 = "three";
    const char* v2 = "one";
    const char* v3 = "two";
    mapPut(map, &k1, (void*)v1);
    mapPut(map, &k2, (void*)v2);
    mapPut(map, &k3, (void*)v3);
    CHECK(mapSize(map) == 3, "map size after puts");
    CHECK(mapContains(map, &k2), "map contains key");
    CHECK(mapGet(map, &k3) == v3, "map get returns value");

    map_idx = 0;
    mapTraverseInOrder(map, map_visit);
    CHECK(map_idx == 3, "map traverse count");
    CHECK(map_order[0] == 1 && map_order[1] == 2 && map_order[2] == 3, "map in-order keys");

    mapRemove(map, &k2);
    CHECK(mapSize(map) == 2, "map size after remove");
    freeMap(map);

    Set* set = createSet(intCompare);
    setAdd(set, &k1);
    setAdd(set, &k2);
    CHECK(setSize(set) == 2, "set size after add");
    CHECK(setContains(set, &k1), "set contains");
    setRemove(set, &k2);
    CHECK(setSize(set) == 1, "set size after remove");
    freeSet(set);
}

static void test_umap_uset(void) {
    UMap* map = createUMap(intHash, intEquals);
    int k1 = 42, k2 = 99;
    const char* v1 = "forty-two";
    const char* v2 = "ninety-nine";
    umapPut(map, &k1, (void*)v1);
    umapPut(map, &k2, (void*)v2);
    CHECK(umapSize(map) == 2, "umap size after puts");
    CHECK(umapContains(map, &k1), "umap contains key");
    CHECK(umapGet(map, &k2) == v2, "umap get value");
    umapRemove(map, &k1);
    CHECK(umapSize(map) == 1, "umap size after remove");
    freeUMap(map);

    USet* set = createUSet(intHash, intEquals);
    usetAdd(set, &k1);
    usetAdd(set, &k2);
    CHECK(usetContains(set, &k1), "uset contains key");
    usetRemove(set, &k1);
    CHECK(!usetContains(set, &k1), "uset removed key");
    freeUSet(set);
}

static size_t edgeCount(GraphVertex* v) {
    size_t count = 0;
    for (GraphEdge* e = v->edges; e != NULL; e = e->next) {
        count++;
    }
    return count;
}

static void test_graph(void) {
    Graph* g = createGraph(false);
    int a = 1, b = 2, c = 3;
    GraphVertex* va = graphAddVertex(g, &a);
    GraphVertex* vb = graphAddVertex(g, &b);
    GraphVertex* vc = graphAddVertex(g, &c);
    CHECK(graphSize(g) == 3, "graph vertex count");

    graphAddEdge(g, va, vb);
    graphAddEdge(g, vb, vc);
    CHECK(edgeCount(va) == 1, "graph edges va");
    CHECK(edgeCount(vb) == 2, "graph edges vb");
    CHECK(edgeCount(vc) == 1, "graph edges vc");

    graphRemoveEdge(g, va, vb);
    CHECK(edgeCount(va) == 0, "graph remove edge va");
    CHECK(edgeCount(vb) == 1, "graph remove edge vb");
    freeGraph(g);
}

static void run_all_tests(void) {
    test_linked_list();
    test_stack();
    test_queue();
    test_deque();
    test_binary_tree();
    test_heap();
    test_map_set();
    test_umap_uset();
    test_graph();
}

int main(void) {
    run_all_tests();
    if (tests_failed == 0) {
        printf("All tests passed (%d checks).\n", tests_run);
        return 0;
    }
    printf("%d/%d checks failed.\n", tests_failed, tests_run);
    return 1;
}
