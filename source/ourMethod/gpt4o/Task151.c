#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* newNode(int item) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

Node* insertRec(Node* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key) node->left = insertRec(node->left, key);
    else if (key > node->key) node->right = insertRec(node->right, key);
    return node;
}

Node* deleteRec(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key) root->left = deleteRec(root->left, key);
    else if (key > root->key) root->right = deleteRec(root->right, key);
    else {
        if (root->left == NULL) return root->right;
        else if (root->right == NULL) return root->left;

        root->key = minValue(root->right);
        root->right = deleteRec(root->right, root->key);
    }
    return root;
}

int minValue(Node* node) {
    int minv = node->key;
    while (node->left != NULL) {
        minv = node->left->key;
        node = node->left;
    }
    return minv;
}

int searchRec(Node* root, int key) {
    if (root == NULL) return 0;
    if (root->key == key) return 1;
    return key < root->key ? searchRec(root->left, key) : searchRec(root->right, key);
}

int main() {
    Node* root = NULL;
    root = insertRec(root, 50);
    insertRec(root, 30);
    insertRec(root, 20);
    insertRec(root, 40);
    insertRec(root, 70);
    insertRec(root, 60);
    insertRec(root, 80);

    printf("%d\n", searchRec(root, 40)); // 1
    printf("%d\n", searchRec(root, 25)); // 0

    root = deleteRec(root, 20);
    printf("%d\n", searchRec(root, 20)); // 0

    root = deleteRec(root, 30);
    printf("%d\n", searchRec(root, 30)); // 0

    root = deleteRec(root, 50);
    printf("%d\n", searchRec(root, 50)); // 0

    return 0;
}