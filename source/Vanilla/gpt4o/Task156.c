#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* newTreeNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void preorderHelper(TreeNode* node) {
    if (node) {
        printf("%d ", node->val);
        preorderHelper(node->left);
        preorderHelper(node->right);
    }
}

void preorderTraversal(TreeNode* root) {
    preorderHelper(root);
}

int main() {
    TreeNode* root = newTreeNode(1);
    root->right = newTreeNode(2);
    root->right->left = newTreeNode(3);

    preorderTraversal(root);
    printf("\n"); // Output: 1 2 3

    TreeNode* root2 = newTreeNode(4);
    root2->left = newTreeNode(5);
    root2->right = newTreeNode(6);
    root2->left->left = newTreeNode(7);
    root2->left->right = newTreeNode(8);

    preorderTraversal(root2);
    printf("\n"); // Output: 4 5 7 8 6

    return 0;
}