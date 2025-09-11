
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main() {
    // Test Case 1: Single node
    struct Node* root1 = newNode(1);
    printf("Test Case 1:\\n");
    printf("Preorder: "); preorder(root1);
    printf("\\nInorder: "); inorder(root1);
    printf("\\nPostorder: "); postorder(root1);
    printf("\\n\\n");

    // Test Case 2: Complete binary tree
    struct Node* root2 = newNode(1);
    root2->left = newNode(2);
    root2->right = newNode(3);
    printf("Test Case 2:\\n");
    printf("Preorder: "); preorder(root2);
    printf("\\nInorder: "); inorder(root2);
    printf("\\nPostorder: "); postorder(root2);
    printf("\\n\\n");

    // Test Case 3: Left skewed tree
    struct Node* root3 = newNode(1);
    root3->left = newNode(2);
    root3->left->left = newNode(3);
    printf("Test Case 3:\\n");
    printf("Preorder: "); preorder(root3);
    printf("\\nInorder: "); inorder(root3);
    printf("\\nPostorder: "); postorder(root3);
    printf("\\n\\n");

    // Test Case 4: Right skewed tree
    struct Node* root4 = newNode(1);
    root4->right = newNode(2);
    root4->right->right = newNode(3);
    printf("Test Case 4:\\n");
    printf("Preorder: "); preorder(root4);
    printf("\\nInorder: "); inorder(root4);
    printf("\\nPostorder: "); postorder(root4);
    printf("\\n\\n");

    // Test Case 5: Complex tree
    struct Node* root5 = newNode(1);
    root5->left = newNode(2);
    root5->right = newNode(3);
    root5->left->left = newNode(4);
    root5->left->right = newNode(5);
    printf("Test Case 5:\\n");
    printf("Preorder: "); preorder(root5);
    printf("\\nInorder: "); inorder(root5);
    printf("\\nPostorder: "); postorder(root5);
    printf("\\n");

    return 0;
}
