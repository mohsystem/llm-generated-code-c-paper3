#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left, * right;
};

struct Node* newNode(int item) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void insertNode(struct Node** root, int key) {
    if (*root == NULL) {
        *root = newNode(key);
    }
    else {
        _insertNode(*root, key);
    }
}

void _insertNode(struct Node* node, int key) {
    if (key < node->key) {
        if (node->left == NULL) {
            node->left = newNode(key);
        }
        else {
            _insertNode(node->left, key);
        }
    }
    else {
        if (node->right == NULL) {
            node->right = newNode(key);
        }
        else {
            _insertNode(node->right, key);
        }
    }
}

void deleteNode(struct Node** root, int key) {
    *root = _deleteNode(*root, key);
}

struct Node* _deleteNode(struct Node* node, int key) {
    if (node == NULL) return node;

    if (key < node->key) {
        node->left = _deleteNode(node->left, key);
    }
    else if (key > node->key) {
        node->right = _deleteNode(node->right, key);
    }
    else {
        if (node->left == NULL) return node->right;
        else if (node->right == NULL) return node->left;

        node->key = _minValue(node->right);
        node->right = _deleteNode(node->right, node->key);
    }
    return node;
}

int _minValue(struct Node* node) {
    int minv = node->key;
    while (node->left != NULL) {
        minv = node->left->key;
        node = node->left;
    }
    return minv;
}

int searchNode(struct Node* root, int key) {
    return _searchNode(root, key);
}

int _searchNode(struct Node* node, int key) {
    if (node == NULL) return 0;

    if (key < node->key) return _searchNode(node->left, key);
    else if (key > node->key) return _searchNode(node->right, key);
    else return 1;
}

void inorder(struct Node* root) {
    _inorder(root);
}

void _inorder(struct Node* node) {
    if (node != NULL) {
        _inorder(node->left);
        printf("%d ", node->key);
        _inorder(node->right);
    }
}

int main() {
    struct Node* root = NULL;

    insertNode(&root, 50);
    insertNode(&root, 30);
    insertNode(&root, 70);
    insertNode(&root, 20);
    insertNode(&root, 40);
    insertNode(&root, 60);
    insertNode(&root, 80);

    printf("Inorder Traversal of the given tree is\n");
    inorder(root);

    printf("\nDelete 20\n");
    deleteNode(&root, 20);
    printf("Inorder Traversal of the modified tree is\n");
    inorder(root);

    printf("\nSearch for 40\n");
    if (searchNode(root, 40)) printf("Node found\n");
    else printf("Node not found\n");

    printf("\nInsert 10\n");
    insertNode(&root, 10);
    printf("Inorder Traversal of the modified tree is\n");
    inorder(root);

    return 0;
}