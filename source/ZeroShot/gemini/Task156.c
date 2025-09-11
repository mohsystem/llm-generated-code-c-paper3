#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}


void preorder(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}


void inorder(struct TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

void postorder(struct TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->val);
    }
}


int main() {
    // Test case 1
    struct TreeNode *root1 = createNode(1);
    root1->right = createNode(2);
    root1->right->left = createNode(3);
    preorder(root1);  // Output: 1 2 3
    printf("\n");

     // Test case 2
    struct TreeNode *root2 = NULL;
    inorder(root2);  // Output:
    printf("\n");

    // Test case 3
    struct TreeNode *root3 = createNode(1);
    postorder(root3); // Output: 1
    printf("\n");


     // Test case 4
    struct TreeNode *root4 = createNode(1);
    root4->left = createNode(2);
    root4->right = createNode(3);
    preorder(root4);  // Output: 1 2 3
    printf("\n");

     // Test case 5
    struct TreeNode *root5 = createNode(1);
    root5->left = createNode(2);
    root5->right = createNode(3);
    root5->left->left = createNode(4);
    root5->left->right = createNode(5);
    inorder(root5);  // Output: 4 2 5 1 3
    printf("\n");

    return 0;
}