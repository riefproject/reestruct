#include "binarytree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>


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
        fprintf(stderr, "Error: Memory allocation failed for root node\n");
        delete(tree);
        return NULL;
    }
    tree->depth = 0;
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
    uint size = 0;
    // Implement a traversal to count the nodes
    return size;
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
}

void inorderTraversal(BinaryTree* tree, void (*visitFunc)(void*)) {
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error: BinaryTree or root is NULL\n");
        return;
    }
}

void postorderTraversal(BinaryTree* tree, void (*visitFunc)(void*)) {
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error: BinaryTree or root is NULL\n");
        return;
    }
}

void levelorderTraversal(BinaryTree* tree, void (*visitFunc)(void*)) {
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error: BinaryTree or root is NULL\n");
        return;
    }
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
    if (tree == NULL || node == NULL) {
        fprintf(stderr, "Error: BinaryTree or BTNode is NULL\n");
        return NULL;
    }
    // Implement logic to find the parent of the node
    // This may require a traversal or maintaining parent pointers in the BTNode structure
    // For now, we will return NULL as a placeholder
    // In a real implementation, you would need to traverse the tree to find the parent
    return NULL; // Placeholder
}

BTNode* getBTNodeSibling(BTNode* node) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return NULL;
    }
    // Implement logic to find the sibling of the node
    // This may require a traversal or maintaining sibling pointers in the BTNode structure
    // For now, we will return NULL as a placeholder
    // In a real implementation, you would need to traverse the tree to find the sibling
    return NULL; // Placeholder
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
}

void setBTNodeRight(BTNode* node, BTNode* right) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return;
    }
    node->right = right;
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
}

void setBTNodeParent(BinaryTree* tree, BTNode* node, BTNode* parent) {
    if (tree == NULL || node == NULL) {
        fprintf(stderr, "Error: BinaryTree or BTNode is NULL\n");
        return;
    }
    // Implement logic to set the parent of the node
    // This may require a traversal or maintaining parent pointers in the BTNode structure
    // For now, we will do nothing as a placeholder
    // In a real implementation, you would need to set the parent pointer in the node structure
    // For now, we will do nothing as a placeholder
}

void setBTNodeSibling(BTNode* node, BTNode* sibling) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return;
    }
    // Implement logic to set the sibling of the node
    // This may require a traversal or maintaining sibling pointers in the BTNode structure
    // For now, we will do nothing as a placeholder
    // In a real implementation, you would need to set the sibling pointer in the node structure
    // For now, we will do nothing as a placeholder
}


/*     TREE OPERATIONS
 * ==================== */
void insertLeft(BinaryTree* tree, BTNode* parent, void* data) {
    if (tree == NULL || parent == NULL) {
        fprintf(stderr, "Error: BinaryTree or parent node is NULL\n");
        return;
    }
    BTNode* newNode = createBTNode(data);
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new node\n");
        return;
    }
    parent->left = newNode;
    // Optionally update the tree depth if needed
}

void insertRight(BinaryTree* tree, BTNode* parent, void* data) {
    if (tree == NULL || parent == NULL) {
        fprintf(stderr, "Error: BinaryTree or parent node is NULL\n");
        return;
    }
    BTNode* newNode = createBTNode(data);
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new node\n");
        return;
    }
    parent->right = newNode;
    // Optionally update the tree depth if needed
}

void removeNode(BinaryTree* tree, BTNode* node) {
    if (tree == NULL || node == NULL) {
        fprintf(stderr, "Error: BinaryTree or node is NULL\n");
        return;
    }
    // Implement logic to remove the node from the tree
    // This may require a traversal or maintaining parent pointers in the BTNode structure
    // For now, we will do nothing as a placeholder
    // In a real implementation, you would need to remove the node and update the tree structure accordingly
}


/*        DESTRUCTOR
 * ==================== */
void destroyBinaryTree(BinaryTree* tree) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return;
    }
    // Implement logic to free the tree and its nodes
    // This may require a traversal or maintaining parent pointers in the BTNode structure
    // For now, we will do nothing as a placeholder
    // In a real implementation, you would need to free the nodes and the tree structure accordingly
    delete(tree->root);
    delete(tree);
}

void destroyBTNode(BTNode* node) {
    if (node == NULL) {
        fprintf(stderr, "Error: BTNode is NULL\n");
        return;
    }
    // Implement logic to free the node and its children
    // This may require a traversal or maintaining parent pointers in the BTNode structure
    // For now, we will do nothing as a placeholder
    // In a real implementation, you would need to free the node and its children accordingly
    delete(node->left);
    delete(node->right);
    delete(node);
}

void clearBinaryTree(BinaryTree* tree) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return;
    }
    // Implement logic to clear the tree and its nodes
    // This may require a traversal or maintaining parent pointers in the BTNode structure
    // For now, we will do nothing as a placeholder
    // In a real implementation, you would need to clear the nodes and the tree structure accordingly
    destroyBinaryTree(tree);
}


/*      PRINT TREE
 * ==================== */
void printBinaryTree(BinaryTree* tree, void (*printFunc)(void*)) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return;
    }
    if (tree->root == NULL) {
        fprintf(stderr, "Error: BinaryTree root is NULL\n");
        return;
    }
    // Implement logic to print the tree using the provided print function
    // This may require a traversal or maintaining parent pointers in the BTNode structure
    // For now, we will do nothing as a placeholder
    // In a real implementation, you would need to traverse the tree and call the print function on each node's data
}

void printBinaryTreeDetailed(BinaryTree* tree, void (*printFunc)(void*)) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BinaryTree is NULL\n");
        return;
    }
    if (tree->root == NULL) {
        fprintf(stderr, "Error: BinaryTree root is NULL\n");
        return;
    }
    // Implement logic to print the tree in a detailed format using the provided print function
    // This may require a traversal or maintaining parent pointers in the BTNode structure
    // For now, we will do nothing as a placeholder
    // In a real implementation, you would need to traverse the tree and call the print function on each node's data
}