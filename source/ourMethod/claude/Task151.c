
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insertRec(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    
    if (data < root->data) {
        root->left = insertRec(root->left, data);
    } else if (data > root->data) {
        root->right = insertRec(root->right, data);
    }
    
    return root;
}

int searchRec(struct Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root != NULL;
    }
    
    if (data < root->data) {
        return searchRec(root->left, data);
    }
    
    return searchRec(root->right, data);
}

int minValue(struct Node* root) {
    int minv = root->data;
    while (root->left != NULL) {
        minv = root->left->data;
        root = root->left;
    }
    return minv;
}

struct Node* deleteRec(struct Node* root, int data) {
    if (root == NULL) {
        return NULL;
    }
    
    if (data < root->data) {
        root->left = deleteRec(root->left, data);
    } else if (data > root->data) {
        root->right = deleteRec(root->right, data);
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
        root->right = deleteRec(root->right, root->data);
    }
    
    return root;
}

void cleanup(struct Node* root) {
    if (root != NULL) {
        cleanup(root->left);
        cleanup(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    
    // Test case 1: Insert and search
    root = insertRec(root, 50);
    root = insertRec(root, 30);
    root = insertRec(root, 70);
    printf("Test 1 - Search 30: %d\\n", searchRec(root, 30));  // Should print 1
    
    // Test case 2: Search non-existent value
    printf("Test 2 - Search 40: %d\\n", searchRec(root, 40));  // Should print 0
    
    // Test case 3: Delete leaf node
    root = deleteRec(root, 30);
    printf("Test 3 - Search 30 after deletion: %d\\n", searchRec(root, 30));  // Should print 0
    
    // Test case 4: Delete node with one child
    root = insertRec(root, 60);
    root = deleteRec(root, 70);
    printf("Test 4 - Search 70 after deletion: %d\\n", searchRec(root, 70));  // Should print 0
    
    // Test case 5: Delete node with two children
    root = insertRec(root, 80);
    root = deleteRec(root, 60);
    printf("Test 5 - Search 60 after deletion: %d\\n", searchRec(root, 60));  // Should print 0
    
    cleanup(root);
    return 0;
}
