#include <stdio.h>
#include <stdlib.h>

///* Comment:  C does not have built-in support for generics like lists used in other examples.  Implementing this would require more extensive code including custom list/vector implementations. This example uses simpler print statements to illustrate the traversal logic.*/

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


void preorder(struct TreeNode *node) {
    if (node != NULL) {
        printf("%d ", node->val);
        preorder(node->left);
        preorder(node->right);
    }
}
void inorder(struct TreeNode *node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%d ", node->val);
        inorder(node->right);
    }
}


void postorder(struct TreeNode *node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        printf("%d ", node->val);
    }
}



int main() {

    // Test case 1
    struct TreeNode *root1 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root1->val = 1;
    root1->left = NULL;
    root1->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root1->right->val = 2;
    root1->right->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root1->right->left->val = 3;
    root1->right->left->left = NULL;
    root1->right->left->right = NULL;
    root1->right->right = NULL;

    printf("Preorder: ");
    preorder(root1);
    printf("\n");
    printf("Inorder: ");
    inorder(root1);
    printf("\n");
    printf("Postorder: ");
    postorder(root1);
    printf("\n");

    // Other Test cases 2-5
    // Add code for other test cases similar to test case 1


    return 0;
}