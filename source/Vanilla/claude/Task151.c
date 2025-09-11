
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->left = node->right = NULL;
    return node;
}

struct Node* insert(struct Node* root, int value) {
    if(root == NULL)
        return newNode(value);
        
    if(value < root->data)
        root->left = insert(root->left, value);
    else if(value > root->data)
        root->right = insert(root->right, value);
        
    return root;
}

int minValue(struct Node* root) {
    int minv = root->data;
    while(root->left != NULL) {
        minv = root->left->data;
        root = root->left;
    }
    return minv;
}

struct Node* deleteNode(struct Node* root, int value) {
    if(root == NULL)
        return root;
        
    if(value < root->data)
        root->left = deleteNode(root->left, value);
    else if(value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        if(root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        root->data = minValue(root->right);
        root->right = deleteNode(root->right, root->data);
    }
    return root;
}

bool search(struct Node* root, int value) {
    if(root == NULL || root->data == value)
        return root != NULL;
        
    if(value < root->data)
        return search(root->left, value);
        
    return search(root->right, value);
}

int main() {
    struct Node* root = NULL;
    
    // Test case 1: Insert elements
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    
    // Test case 2: Search for existing element
    printf("Search 30: %d\\n", search(root, 30));
    
    // Test case 3: Search for non-existing element
    printf("Search 40: %d\\n", search(root, 40));
    
    // Test case 4: Delete leaf node
    root = deleteNode(root, 30);
    printf("After deleting 30, Search 30: %d\\n", search(root, 30));
    
    // Test case 5: Delete node with two children
    root = insert(root, 30);
    root = insert(root, 40);
    root = deleteNode(root, 30);
    printf("After re-deleting 30, Search 40: %d\\n", search(root, 40));
    
    return 0;
}
