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

void buildParentMap(TreeNode* node, TreeNode* parent, TreeNode** parentMap, int* index) {
    if (node == NULL) return;
    parentMap[node->val] = parent;
    for (int i = 0; i < node->childCount; i++) {
        buildParentMap(node->children[i], node, parentMap, index);
    }
}

TreeNode* findNode(TreeNode* node, int target) {
    if (node == NULL || node->val == target) return node;
    for (int i = 0; i < node->childCount; i++) {
        TreeNode* result = findNode(node->children[i], target);
        if (result != NULL) return result;
    }
    return NULL;
}

void reorient(TreeNode* node, TreeNode* newParent, TreeNode** parentMap) {
    if (node == NULL) return;
    TreeNode* originalParent = parentMap[node->val];
    if (originalParent != NULL) {
        node->children = (TreeNode**)realloc(node->children, (node->childCount + 1) * sizeof(TreeNode*));
        node->children[node->childCount++] = originalParent;
        
        for (int i = 0; i < originalParent->childCount; i++) {
            if (originalParent->children[i] == node) {
                for (int j = i; j < originalParent->childCount - 1; j++) {
                    originalParent->children[j] = originalParent->children[j + 1];
                }
                originalParent->childCount--;
                break;
            }
        }
        
        reorient(originalParent, node, parentMap);
    }
    if (newParent != NULL) {
        for (int i = 0; i < node->childCount; i++) {
            if (node->children[i] == newParent) {
                for (int j = i; j < node->childCount - 1; j++) {
                    node->children[j] = node->children[j + 1];
                }
                node->childCount--;
                break;
            }
        }
    }
}

TreeNode* reorientTree(TreeNode* root, int target) {
    TreeNode* parentMap[10] = {NULL};
    buildParentMap(root, NULL, parentMap, NULL);
    TreeNode* newRoot = findNode(root, target);
    reorient(newRoot, NULL, parentMap);
    return newRoot;
}

int main() {
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

    root->children = (TreeNode**)malloc(3 * sizeof(TreeNode*));
    root->children[0] = node1;
    root->children[1] = node2;
    root->children[2] = node3;
    root->childCount = 3;

    node1->children = (TreeNode**)malloc(2 * sizeof(TreeNode*));
    node1->children[0] = node4;
    node1->children[1] = node5;
    node1->childCount = 2;

    node2->children = (TreeNode**)malloc(2 * sizeof(TreeNode*));
    node2->children[0] = node6;
    node2->children[1] = node7;
    node2->childCount = 2;

    node3->children = (TreeNode**)malloc(2 * sizeof(TreeNode*));
    node3->children[0] = node8;
    node3->children[1] = node9;
    node3->childCount = 2;

    TreeNode* newRoot = reorientTree(root, 6);
    printf("New root value: %d\n", newRoot->val);

    newRoot = reorientTree(root, 3);
    printf("New root value: %d\n", newRoot->val);

    newRoot = reorientTree(root, 9);
    printf("New root value: %d\n", newRoot->val);

    newRoot = reorientTree(root, 0);
    printf("New root value: %d\n", newRoot->val);

    newRoot = reorientTree(root, 7);
    printf("New root value: %d\n", newRoot->val);

    return 0;
}