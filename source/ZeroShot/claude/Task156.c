
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int item) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    // Test Case 1: Single node tree
    struct Node* root1 = newNode(1);
    printf("Test Case 1:\\n");
    printf("Preorder: "); preorder(root1); printf("\\n");
    printf("Inorder: "); inorder(root1); printf("\\n");
    printf("Postorder: "); postorder(root1); printf("\\n");
    
    // Test Case 2: Complete binary tree
    struct Node* root2 = newNode(1);
    root2->left = newNode(2);
    root2->right = newNode(3);
    root2->left->left = newNode(4);
    root2->left->right = newNode(5);
    printf("\\nTest Case 2:\\n");
    printf("Preorder: "); preorder(root2); printf("\\n");
    printf("Inorder: "); inorder(root2); printf("\\n");
    printf("Postorder: "); postorder(root2); printf("\\n");
    
    // Test Case 3: Left skewed tree
    struct Node* root3 = newNode(1);
    root3->left = newNode(2);
    root3->left->left = newNode(3);
    printf("\\nTest Case 3:\\n");
    printf("Preorder: "); preorder(root3); printf("\\n");
    printf("Inorder: "); inorder(root3); printf("\\n");
    printf("Postorder: "); postorder(root3); printf("\\n");
    
    // Test Case 4: Right skewed tree
    struct Node* root4 = newNode(1);
    root4->right = newNode(2);
    root4->right->right = newNode(3);
    printf("\\nTest Case 4:\\n");
    printf("Preorder: "); preorder(root4); printf("\\n");
    printf("Inorder: "); inorder(root4); printf("\\n");
    printf("Postorder: "); postorder(root4); printf("\\n");
    
    // Test Case 5: Empty tree
    struct Node* root5 = NULL;
    printf("\\nTest Case 5:\\n");
    printf("Preorder: "); preorder(root5); printf("\\n");
    printf("Inorder: "); inorder(root5); printf("\\n");
    printf("Postorder: "); postorder(root5); printf("\\n");
    
    return 0;
}
