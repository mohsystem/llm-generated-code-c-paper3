#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node** children;
    int children_count;
} Node;

Node* reparent(Node* root, int newRootData) {
    Node* newRoot = findNode(root, newRootData);
    if (newRoot == NULL) {
        return root;
    }
    Node* parent = findParent(root, newRootData);
    if (parent != NULL) {
        for (int i = 0; i < parent->children_count; i++) {
            if (parent->children[i] == newRoot) {
                for (int j = i; j < parent->children_count - 1; j++) {
                    parent->children[j] = parent->children[j + 1];
                }
                parent->children_count--;
                break;
            }
        }
    }
    for (int i = 0; i < newRoot->children_count; i++) {
        reparent(newRoot->children[i], newRootData);
    }
    return newRoot;
}

Node* findNode(Node* root, int data) {
    if (root->data == data) {
        return root;
    }
    for (int i = 0; i < root->children_count; i++) {
        Node* found = findNode(root->children[i], data);
        if (found != NULL) {
            return found;
        }
    }
    return NULL;
}

Node* findParent(Node* root, int data) {
    for (int i = 0; i < root->children_count; i++) {
        if (root->children[i]->data == data) {
            return root;
        }
        Node* found = findParent(root->children[i], data);
        if (found != NULL) {
            return found;
        }
    }
    return NULL;
}

int main() {
    // Test cases here
    return 0;
}