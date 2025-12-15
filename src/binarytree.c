// Created by: Arief F-sa Wijaya

#include "binarytree.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static uint countNodes(const BTNode* node) {
    if (node == NULL) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

static uint computeDepth(const BTNode* node) {
    if (node == NULL) return 0;
    uint leftDepth = computeDepth(node->left);
    uint rightDepth = computeDepth(node->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

static void preorderHelper(BTNode* node, void (*visitFunc)(void*)) {
    if (node == NULL) return;
    visitFunc(node->data);
    preorderHelper(node->left, visitFunc);
    preorderHelper(node->right, visitFunc);
}

static void inorderHelper(BTNode* node, void (*visitFunc)(void*)) {
    if (node == NULL) return;
    inorderHelper(node->left, visitFunc);
    visitFunc(node->data);
    inorderHelper(node->right, visitFunc);
}

static void postorderHelper(BTNode* node, void (*visitFunc)(void*)) {
    if (node == NULL) return;
    postorderHelper(node->left, visitFunc);
    postorderHelper(node->right, visitFunc);
    visitFunc(node->data);
}

static void levelorderHelper(BTNode* root, void (*visitFunc)(void*)) {
    if (root == NULL) return;
    size_t capacity = 16;
    size_t front = 0;
    size_t back = 0;
    BTNode** queue = (BTNode**)malloc(capacity * sizeof(BTNode*));
    if (queue == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for traversal queue\n");
        return;
    }

    queue[back++] = root;
    while (front < back) {
        BTNode* node = queue[front++];
        visitFunc(node->data);
        if (node->left != NULL) {
            if (back >= capacity) {
                capacity *= 2;
                BTNode** resized = (BTNode**)realloc(queue, capacity * sizeof(BTNode*));
                if (resized == NULL) {
                    fprintf(stderr, "Error: Memory allocation failed during traversal resize\n");
                    free(queue);
                    return;
                }
                queue = resized;
            }
            queue[back++] = node->left;
        }
        if (node->right != NULL) {
            if (back >= capacity) {
                capacity *= 2;
                BTNode** resized = (BTNode**)realloc(queue, capacity * sizeof(BTNode*));
                if (resized == NULL) {
                    fprintf(stderr, "Error: Memory allocation failed during traversal resize\n");
                    free(queue);
                    return;
                }
                queue = resized;
            }
            queue[back++] = node->right;
        }
    }
    free(queue);
}

static void destroySubtree(BTNode* node) {
    if (node == NULL) return;
    destroySubtree(node->left);
    destroySubtree(node->right);
    delete(node);
}

static void updateDepth(BinaryTree* tree) {
    tree->depth = computeDepth(tree->root);
}

/*      CONSTRUCTOR
 * ==================== */
BinaryTree* createBinaryTree(void* data) {
    BinaryTree* tree = new(BinaryTree);
    if (tree == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for BinaryTree\n");
        return NULL;
    }
    tree->root = createBTNode(data);
    if (tree->root == NULL) {
        delete(tree);
        return NULL;
    }
    tree->root->parent = NULL;
    tree->depth = computeDepth(tree->root);
    return tree;
}

BTNode* createBTNode(void* data) {
    BTNode* node = new(BTNode);
    if (node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for BTNode\n");
        return NULL;
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}


/*      STATUS CHECKS
 * ==================== */
bool isBinaryTreeEmpty(BinaryTree* tree) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return true;
    }
    return (tree->root == NULL);
}

uint getBinaryTreeSize(BinaryTree* tree) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return 0;
    }
    return countNodes(tree->root);
}

bool isLeafNode(BTNode* node) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return false;
    }
    return (node->left == NULL && node->right == NULL);
}


/*      TRAVERSAL
 * ==================== */
void preorderTraversal(BinaryTree* tree, void (*visitFunc)(void*)) {
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error: BinaryTree or root is NULL\n");
        return;
    }
    if (visitFunc == NULL) return;
    preorderHelper(tree->root, visitFunc);
}

void inorderTraversal(BinaryTree* tree, void (*visitFunc)(void*)) {
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error: BinaryTree or root is NULL\n");
        return;
    }
    if (visitFunc == NULL) return;
    inorderHelper(tree->root, visitFunc);
}

void postorderTraversal(BinaryTree* tree, void (*visitFunc)(void*)) {
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error: BinaryTree or root is NULL\n");
        return;
    }
    if (visitFunc == NULL) return;
    postorderHelper(tree->root, visitFunc);
}

void levelorderTraversal(BinaryTree* tree, void (*visitFunc)(void*)) {
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error: BinaryTree or root is NULL\n");
        return;
    }
    if (visitFunc == NULL) return;
    levelorderHelper(tree->root, visitFunc);
}


/*        GETTERS
 * ==================== */
void* getBTNodeData(BTNode* node) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return NULL;
    }
    return node->data;
}

BTNode* getBTNodeLeft(BTNode* node) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return NULL;
    }
    return node->left;
}

BTNode* getBTNodeRight(BTNode* node) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return NULL;
    }
    return node->right;
}

uint getBinaryTreeDepth(BinaryTree* tree) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return 0;
    }
    return tree->depth;
}

BTNode* getBinaryTreeRoot(BinaryTree* tree) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return NULL;
    }
    return tree->root;
}

BTNode* getBTNodeParent(BinaryTree* tree, BTNode* node) {
    (void)tree;
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return NULL;
    }
    return node->parent;
}

BTNode* getBTNodeSibling(BTNode* node) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return NULL;
    }
    if (node->parent == NULL) return NULL;
    if (node->parent->left == node) return node->parent->right;
    if (node->parent->right == node) return node->parent->left;
    return NULL;
}


/*        SETTERS
 * ==================== */
void setBTNodeData(BTNode* node, void* data) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return;
    }
    node->data = data;
}

void setBTNodeLeft(BTNode* node, BTNode* left) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return;
    }
    node->left = left;
    if (left != NULL) left->parent = node;
}

void setBTNodeRight(BTNode* node, BTNode* right) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return;
    }
    node->right = right;
    if (right != NULL) right->parent = node;
}

void setBinaryTreeDepth(BinaryTree* tree, uint depth) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return;
    }
    tree->depth = depth;
}

void setBinaryTreeRoot(BinaryTree* tree, BTNode* root) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return;
    }
    tree->root = root;
    if (tree->root != NULL) tree->root->parent = NULL;
    updateDepth(tree);
}

void setBTNodeParent(BinaryTree* tree, BTNode* node, BTNode* parent) {
    (void)tree;
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return;
    }
    node->parent = parent;
}

void setBTNodeSibling(BTNode* node, BTNode* sibling) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return;
    }
    if (node->parent == NULL) return;
    if (node->parent->left == node) {
        node->parent->right = sibling;
    } else if (node->parent->right == node) {
        node->parent->left = sibling;
    }
    if (sibling != NULL) sibling->parent = node->parent;
}


/*     TREE OPERATIONS
 * ==================== */
void insertLeft(BinaryTree* tree, BTNode* parent, void* data) {
    if (tree == NULL || parent == NULL) {
        fprintf(stderr, "Error: BinaryTree or parent node is NULL\n");
        return;
    }
    BTNode* newNode = createBTNode(data);
    if (newNode == NULL) return;

    newNode->left = parent->left;
    if (newNode->left != NULL) newNode->left->parent = newNode;
    parent->left = newNode;
    newNode->parent = parent;
    updateDepth(tree);
}

void insertRight(BinaryTree* tree, BTNode* parent, void* data) {
    if (tree == NULL || parent == NULL) {
        fprintf(stderr, "Error: BinaryTree or parent node is NULL\n");
        return;
    }
    BTNode* newNode = createBTNode(data);
    if (newNode == NULL) return;

    newNode->right = parent->right;
    if (newNode->right != NULL) newNode->right->parent = newNode;
    parent->right = newNode;
    newNode->parent = parent;
    updateDepth(tree);
}

void removeNode(BinaryTree* tree, BTNode* node) {
    if (tree == NULL || node == NULL) {
        fprintf(stderr, "Error: BinaryTree or node is NULL\n");
        return;
    }
    if (node->parent != NULL) {
        if (node->parent->left == node) {
            node->parent->left = NULL;
        } else if (node->parent->right == node) {
            node->parent->right = NULL;
        }
    } else {
        tree->root = NULL;
    }
    destroySubtree(node);
    updateDepth(tree);
}


/*        DESTRUCTOR
 * ==================== */
void destroyBinaryTree(BinaryTree* tree) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return;
    }
    destroySubtree(tree->root);
    delete(tree);
}

void destroyBTNode(BTNode* node) {
    destroySubtree(node);
}

void clearBinaryTree(BinaryTree* tree) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return;
    }
    destroySubtree(tree->root);
    tree->root = NULL;
    tree->depth = 0;
}


/*      PRINT TREE
 * ==================== */
void printBinaryTree(BinaryTree* tree, void (*printFunc)(void*)) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return;
    }
    if (tree->root == NULL || printFunc == NULL) return;
    inorderHelper(tree->root, printFunc);
    printf("\n");
}

static void printDetailed(BTNode* node, void (*printFunc)(void*), uint depth) {
    if (node == NULL) return;
    printDetailed(node->right, printFunc, depth + 1);
    for (uint i = 0; i < depth; i++) {
        printf("  ");
    }
    printFunc(node->data);
    printf("\n");
    printDetailed(node->left, printFunc, depth + 1);
}

void printBinaryTreeDetailed(BinaryTree* tree, void (*printFunc)(void*)) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return;
    }
    if (tree->root == NULL || printFunc == NULL) return;
    printDetailed(tree->root, printFunc, 0);
}
