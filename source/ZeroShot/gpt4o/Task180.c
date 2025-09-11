#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode** children;
    int childCount;
} TreeNode;

TreeNode* createNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->children = NULL;
    node->childCount = 0;
    return node;
}

void addChild(TreeNode* parent, TreeNode* child) {
    parent->childCount++;
    parent->children = (TreeNode**)realloc(parent->children, parent->childCount * sizeof(TreeNode*));
    parent->children[parent->childCount - 1] = child;
}

void reorientTree(TreeNode* parent, TreeNode* node) {
    if (parent != NULL) {
        int i;
        for (i = 0; i < node->childCount; i++) {
            if (node->children[i] == parent) {
                break;
            }
        }
        for (int j = i; j < node->childCount - 1; j++) {
            node->children[j] = node->children[j + 1];
        }
        node->childCount--;
        node->children = (TreeNode**)realloc(node->children, node->childCount * sizeof(TreeNode*));
        addChild(node, parent);
    }
    for (int i = 0; i < node->childCount; i++) {
        reorientTree(node, node->children[i]);
    }
}

TreeNode* findNode(TreeNode* node, int val) {
    if (node->val == val) {
        return node;
    }
    for (int i = 0; i < node->childCount; i++) {
        TreeNode* found = findNode(node->children[i], val);
        if (found != NULL) {
            return found;
        }
    }
    return NULL;
}

TreeNode* reparentTree(TreeNode* root, int newRootVal) {
    TreeNode* newRoot = findNode(root, newRootVal);
    if (newRoot != NULL) {
        reorientTree(NULL, newRoot);
    }
    return newRoot;
}

int main() {
    // Test case 1
    TreeNode* root1 = createNode(0);
    TreeNode* node1 = createNode(1);
    TreeNode* node2 = createNode(2);
    TreeNode* node3 = createNode(3);
    addChild(root1, node1);
    addChild(root1, node2);
    addChild(root1, node3);
    addChild(node1, createNode(4));
    addChild(node1, createNode(5));
    addChild(node2, createNode(6));
    addChild(node2, createNode(7));
    addChild(node3, createNode(8));
    addChild(node3, createNode(9));
    TreeNode* newRoot1 = reparentTree(root1, 6);
    
    // Test case 2
    TreeNode* root2 = createNode(0);
    TreeNode* node4 = createNode(1);
    TreeNode* node5 = createNode(2);
    TreeNode* node6 = createNode(3);
    addChild(root2, node4);
    addChild(root2, node5);
    addChild(root2, node6);
    addChild(node4, createNode(4));
    addChild(node5, createNode(5));
    addChild(node6, createNode(6));
    TreeNode* newRoot2 = reparentTree(root2, 5);
    
    // Test case 3
    TreeNode* root3 = createNode(0);
    TreeNode* node7 = createNode(1);
    addChild(root3, node7);
    addChild(node7, createNode(2));
    addChild(node7, createNode(3));
    TreeNode* newRoot3 = reparentTree(root3, 3);
    
    // Test case 4
    TreeNode* root4 = createNode(0);
    TreeNode* node8 = createNode(1);
    TreeNode* node9 = createNode(2);
    addChild(root4, node8);
    addChild(node8, node9);
    addChild(node9, createNode(3));
    TreeNode* newRoot4 = reparentTree(root4, 2);
    
    // Test case 5
    TreeNode* root5 = createNode(0);
    TreeNode* node10 = createNode(1);
    addChild(root5, node10);
    addChild(node10, createNode(2));
    TreeNode* newRoot5 = reparentTree(root5, 1);

    return 0;
}