
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* insert(struct Node* node, int value) {
    if (node == NULL) {
        return newNode(value);
    }
    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    return node;
}

int minValue(struct Node* node) {
    int minv = node->data;
    while (node->left != NULL) {
        minv = node->left->data;
        node = node->left;
    }
    return minv;
}

struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL) {
        return NULL;
    }
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        root->data = minValue(root->right);
        root->right = deleteNode(root->right, root->data);
    }
    return root;
}

int search(struct Node* root, int value) {
    if (root == NULL || root->data == value) {
        return root != NULL;
    }
    if (value < root->data) {
        return search(root->left, value);
    }
    return search(root->right, value);
}

int main() {
    struct Node* root = NULL;
    
    // Test case 1: Insert elements
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    printf("Search 30: %d\\n", search(root, 30));
    
    // Test case 2: Search non-existent element
    printf("Search 40: %d\\n", search(root, 40));
    
    // Test case 3: Delete leaf node
    root = deleteNode(root, 30);
    printf("Search after delete 30: %d\\n", search(root, 30));
    
    // Test case 4: Delete node with one child
    root = insert(root, 60);
    root = deleteNode(root, 70);
    printf("Search after delete 70: %d\\n", search(root, 70));
    
    // Test case 5: Delete node with two children
    root = insert(root, 70);
    root = insert(root, 65);
    root = deleteNode(root, 60);
    printf("Search after delete 60: %d\\n", search(root, 60));
    
    return 0;
}
