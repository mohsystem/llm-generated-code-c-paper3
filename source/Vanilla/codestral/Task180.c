#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* parent;
    struct Node** children;
    int children_count;
} Node;

Node* newNode(int data) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->parent = NULL;
    node->children = malloc(sizeof(Node*) * 10); // Assuming maximum 10 children for simplicity
    node->children_count = 0;
    return node;
}

void addChild(Node* parent, Node* child) {
    parent->children[parent->children_count++] = child;
    child->parent = parent;
}

void reparent(Node* node) {
    if (node->parent != NULL) {
        Node* parent = node->parent;
        for (int i = 0; i < parent->children_count; i++) {
            if (parent->children[i] == node) {
                parent->children[i] = parent->children[parent->children_count - 1];
                parent->children_count--;
                break;
            }
        }
        node->parent = NULL;
        addChild(node, parent);
        reparent(parent);
    }
}

int main() {
    Node* root = newNode(0);
    Node* node1 = newNode(1);
    Node* node2 = newNode(2);
    Node* node3 = newNode(3);

    addChild(root, node1);
    addChild(root, node2);
    addChild(root, node3);

    reparent(node2);
    // Now, the tree is reparented on node2

    return 0;
}