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
    parent->children = (TreeNode**)realloc(parent->children, sizeof(TreeNode*) * (parent->childCount + 1));
    parent->children[parent->childCount++] = child;
}

void buildParentMap(TreeNode* node, TreeNode* parent, TreeNode** parentMap) {
    if (node) {
        parentMap[node->val] = parent;
        for (int i = 0; i < node->childCount; ++i) {
            buildParentMap(node->children[i], node, parentMap);
        }
    }
}

void reparent(TreeNode* node, TreeNode* parent, TreeNode** parentMap) {
    if (node) {
        TreeNode** newChildren = (TreeNode**)malloc(sizeof(TreeNode*) * (node->childCount + (parent ? 1 : 0)));
        int newChildCount = 0;

        for (int i = 0; i < node->childCount; ++i) {
            if (node->children[i] != parent) {
                newChildren[newChildCount++] = node->children[i];
            }
        }
        if (parent) {
            newChildren[newChildCount++] = parent;
        }

        TreeNode* originalParent = parentMap[node->val];
        if (originalParent) {
            for (int i = 0; i < originalParent->childCount; ++i) {
                if (originalParent->children[i] == node) {
                    for (int j = i; j < originalParent->childCount - 1; ++j) {
                        originalParent->children[j] = originalParent->children[j + 1];
                    }
                    --originalParent->childCount;
                    break;
                }
            }
        }

        free(node->children);
        node->children = newChildren;
        node->childCount = newChildCount;

        for (int i = 0; i < node->childCount; ++i) {
            reparent(node->children[i], node, parentMap);
        }
    }
}

TreeNode* reparentTree(TreeNode* root, int newRootVal) {
    TreeNode** parentMap = (TreeNode**)calloc(10, sizeof(TreeNode*)); // Assuming max value is 9
    buildParentMap(root, NULL, parentMap);

    TreeNode* newRoot = parentMap[newRootVal];
    reparent(newRoot, NULL, parentMap);
    free(parentMap);
    return newRoot;
}

int main() {
    // Test cases
    TreeNode* root = createNode(0);
    TreeNode* node1 = createNode(1);
    TreeNode* node2 = createNode(2);
    TreeNode* node3 = createNode(3);
    TreeNode* node4 = createNode(4);
    TreeNode* node5 = createNode(5);
    TreeNode* node6 = createNode(6);
    TreeNode* node7 = createNode(7);
    TreeNode* node8 = createNode(8);
    TreeNode* node9 = createNode(9);

    addChild(root, node1);
    addChild(root, node2);
    addChild(root, node3);
    addChild(node1, node4);
    addChild(node1, node5);
    addChild(node2, node6);
    addChild(node2, node7);
    addChild(node3, node8);
    addChild(node3, node9);

    TreeNode* newRoot = reparentTree(root, 6);
    printf("%d\n", newRoot->val); // Output: 6

    TreeNode* newRoot2 = reparentTree(root, 3);
    printf("%d\n", newRoot2->val); // Output: 3

    TreeNode* newRoot3 = reparentTree(root, 0);
    printf("%d\n", newRoot3->val); // Output: 0

    TreeNode* newRoot4 = reparentTree(root, 7);
    printf("%d\n", newRoot4->val); // Output: 7

    TreeNode* newRoot5 = reparentTree(root, 9);
    printf("%d\n", newRoot5->val); // Output: 9

    return 0;
}