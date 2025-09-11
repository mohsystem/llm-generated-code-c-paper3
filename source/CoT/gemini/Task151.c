#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}


struct Node* insert(struct Node *root, int key) {

    if (root == NULL) return newNode(key);


    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);


    return root;
}


struct Node * minValueNode(struct Node* node) {
    struct Node* current = node;


    while (current && current->left != NULL)
        current = current->left;

    return current;
}


struct Node* deleteNode(struct Node* root, int key) {

    if (root == NULL) return root;


    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);


    else {

        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }


        struct Node* temp = minValueNode(root->right);


        root->data = temp->data;


        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}




bool search(struct Node *root, int key) {

    if (root == NULL || root->data == key)
        return root != NULL;


    if (root->data < key)
        return search(root->right, key);


    return search(root->left, key);
}


int main() {
    struct Node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    printf("%s\n", search(root, 40) ? "true" : "false"); //true
    deleteNode(root, 20);
    printf("%s\n", search(root, 20) ? "true" : "false"); //false
    insert(root, 10);
    printf("%s\n", search(root, 10) ? "true" : "false"); //true
     deleteNode(root, 50);
    printf("%s\n", search(root, 50) ? "true" : "false"); //false
    insert(root, 90);
    printf("%s\n", search(root, 90) ? "true" : "false"); //true
    deleteNode(root, 10);
    printf("%s\n", search(root, 10) ? "true" : "false"); //false
    return 0;
}