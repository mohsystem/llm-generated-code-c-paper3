#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void preorderTraversal(TreeNode* node) {
    if (!node) return;
    printf("%d ", node->value);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

void inorderTraversal(TreeNode* node) {
    if (!node) return;
    inorderTraversal(node->left);
    printf("%d ", node->value);
    inorderTraversal(node->right);
}

void postorderTraversal(TreeNode* node) {
    if (!node) return;
    postorderTraversal(node->left);
    postorderTraversal(node->right);
    printf("%d ", node->value);
}

void freeTree(TreeNode* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    // Test 1: Preorder
    printf("Preorder: ");
    preorderTraversal(root);
    printf("\n");

    // Test 2: Inorder
    printf("Inorder: ");
    inorderTraversal(root);
    printf("\n");

    // Test 3: Postorder
    printf("Postorder: ");
    postorderTraversal(root);
    printf("\n");

    // Additional Tests
    TreeNode* newRoot = createNode(6);
    newRoot->left = createNode(7);
    newRoot->right = createNode(8);

    // Test 4: Preorder on new tree
    printf("Preorder New Tree: ");
    preorderTraversal(newRoot);
    printf("\n");

    // Test 5: Inorder on new tree
    printf("Inorder New Tree: ");
    inorderTraversal(newRoot);
    printf("\n");

    // Free memory
    freeTree(root);
    freeTree(newRoot);

    return 0;
}