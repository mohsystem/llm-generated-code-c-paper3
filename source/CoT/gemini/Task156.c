#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}


int main() {
    // Test case 1
    struct Node* root1 = createNode(1);
    root1->right = createNode(2);
    root1->right->left = createNode(3);
    printf("Preorder Traversal: ");
    preorderTraversal(root1);
    printf("\n");

    // Test case 2
    struct Node *root2 = NULL;
    printf("Preorder Traversal: ");
    preorderTraversal(root2);
    printf("\n");


    // Test case 3
    struct Node* root3 = createNode(1);
    printf("Preorder Traversal: ");
    preorderTraversal(root3);
    printf("\n");


    // Test case 4
    struct Node* root4 = createNode(1);
    root4->left = createNode(2);
    printf("Inorder Traversal: ");
    inorderTraversal(root4);
    printf("\n");

    // Test case 5
    struct Node* root5 = createNode(1);
    root5->right = createNode(2);
    printf("Postorder Traversal: ");
    postorderTraversal(root5);
    printf("\n");


    return 0;
}