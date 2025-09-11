#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left, *right;
};

struct Task151 {
    struct Node *root;
};

struct Task151* createTask151() {
    struct Task151 *tree = (struct Task151*)malloc(sizeof(struct Task151));
    tree->root = NULL;
    return tree;
}

struct Node* newNode(int key) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

void insertKey(struct Task151 *tree, int key) {
    tree->root = insertKeyRec(tree->root, key);
}

struct Node* insertKeyRec(struct Node *root, int key) {
    if (root == NULL) {
        return newNode(key);
    }
    if (key < root->key)
        root->left = insertKeyRec(root->left, key);
    else if (key > root->key)
        root->right = insertKeyRec(root->right, key);
    return root;
}

void inorder(struct Task151 *tree) {
    inorderRec(tree->root);
}

void inorderRec(struct Node *root) {
    if (root != NULL) {
        inorderRec(root->left);
        printf("%d ", root->key);
        inorderRec(root->right);
    }
}

int searchRecursively(struct Task151 *tree, int value) {
    return searchRecursivelyRec(tree->root, value);
}

int searchRecursivelyRec(struct Node *root, int value) {
    if (root == NULL)
        return 0;
    if (value == root->key)
        return 1;
    if (value < root->key)
        return searchRecursivelyRec(root->left, value);
    return searchRecursivelyRec(root->right, value);
}

struct Node* deleteRec(struct Task151 *tree, int key) {
    tree->root = deleteRecRec(tree->root, key);
    return tree->root;
}

struct Node* deleteRecRec(struct Node *root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteRecRec(root->left, key);
    else if (key > root->key)
        root->right = deleteRecRec(root->right, key);
    else {
        if (root->left == NULL)
            return root->right;
        else if (root->right == NULL)
            return root->left;

        root->key = minValue(root->right);
        root->right = deleteRecRec(root->right, root->key);
    }
    return root;
}

int minValue(struct Node *root) {
    int minv = root->key;
    while (root->left != NULL) {
        minv = root->left->key;
        root = root->left;
    }
    return minv;
}

int main() {
    struct Task151 *tree = createTask151();

    // Test cases
    insertKey(tree, 8);
    insertKey(tree, 3);
    insertKey(tree, 10);
    insertKey(tree, 1);
    insertKey(tree, 6);
    insertKey(tree, 14);
    insertKey(tree, 4);
    insertKey(tree, 7);
    insertKey(tree, 13);

    printf("Search Value 10 is in tree? %s\n", searchRecursively(tree, 10) ? "True" : "False");
    printf("Search Value 15 is in tree? %s\n", searchRecursively(tree, 15) ? "True" : "False");

    inorder(tree);
    printf("\n");
    deleteRec(tree, 10);
    inorder(tree);

    return 0;
}