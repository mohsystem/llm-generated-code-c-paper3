
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL)
        return createNode(data);
        
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
        
    return root;
}

bool search(Node* root, int data) {
    if (root == NULL || root->data == data)
        return root != NULL;
        
    if (data < root->data)
        return search(root->left, data);
        
    return search(root->right, data);
}

int minValue(Node* root) {
    int minv = root->data;
    while (root->left != NULL) {
        minv = root->left->data;
        root = root->left;
    }
    return minv;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL)
        return root;
        
    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        
        root->data = minValue(root->right);
        root->right = deleteNode(root->right, root->data);
    }
    return root;
}

int main() {
    Node* root = NULL;
    
    // Test Case 1: Insert elements
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    
    // Test Case 2: Search elements
    printf("Search 20: %d\\n", search(root, 20));  // 1
    printf("Search 60: %d\\n", search(root, 60));  // 0
    
    // Test Case 3: Delete leaf node
    root = deleteNode(root, 20);
    printf("Search after delete 20: %d\\n", search(root, 20));  // 0
    
    // Test Case 4: Delete node with one child
    root = insert(root, 60);
    root = insert(root, 80);
    root = deleteNode(root, 70);
    printf("Search after delete 70: %d\\n", search(root, 70));  // 0
    
    // Test Case 5: Delete node with two children
    root = deleteNode(root, 30);
    printf("Search after delete 30: %d\\n", search(root, 30));  // 0
    
    return 0;
}
