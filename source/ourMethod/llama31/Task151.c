#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int item) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* insertKey(struct Node* root, int key) {
    if (root == NULL) {
        root = newNode(key);
        return root;
    }
    if (key < root->key)
        root->left = insertKey(root->left, key);
    else if (key > root->key)
        root->right = insertKey(root->right, key);
    return root;
}

int searchNode(struct Node* root, int key) {
    if (root == NULL)
        return 0;
    if (key == root->key)
        return 1;
    if (key < root->key)
        return searchNode(root->left, key);
    return searchNode(root->right, key);
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL)
            return root->right;
        else if (root->right == NULL)
            return root->left;
        struct Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int main() {
    struct Node* root = NULL;
    root = insertKey(root, 10);
    root = insertKey(root, 5);
    root = insertKey(root, 20);
    root = insertKey(root, 4);
    root = insertKey(root, 8);
    root = insertKey(root, 15);
    root = insertKey(root, 25);

    printf("Search Value 10: %d\n", searchNode(root, 10));
    printf("Search Value 2: %d\n", searchNode(root, 2));
    root = deleteNode(root, 10);
    printf("Search Value 10 after deletion: %d\n", searchNode(root, 10));

    return 0;
}