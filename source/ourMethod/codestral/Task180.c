#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* parent;
    struct Node** children;
    int children_count;
} Node;

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->parent = NULL;
    node->children = NULL;
    node->children_count = 0;
    return node;
}

void add_child(Node* parent, Node* child) {
    child->parent = parent;
    parent->children_count++;
    parent->children = (Node**)realloc(parent->children, parent->children_count * sizeof(Node*));
    parent->children[parent->children_count - 1] = child;
}

void remove_child(Node* parent, Node* child) {
    for (int i = 0; i < parent->children_count; i++) {
        if (parent->children[i] == child) {
            for (int j = i; j < parent->children_count - 1; j++) {
                parent->children[j] = parent->children[j + 1];
            }
            parent->children_count--;
            parent->children = (Node**)realloc(parent->children, parent->children_count * sizeof(Node*));
            break;
        }
    }
}

void reparent(Node* node, Node* parent) {
    if (node->parent != NULL) {
        remove_child(node->parent, node);
    }
    node->parent = parent;
    if (parent != NULL) {
        add_child(parent, node);
    }
}

int main() {
    Node* root = create_node(0);
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    Node* node3 = create_node(3);
    Node* node4 = create_node(4);
    Node* node5 = create_node(5);
    Node* node6 = create_node(6);
    Node* node7 = create_node(7);
    Node* node8 = create_node(8);
    Node* node9 = create_node(9);

    add_child(root, node1);
    add_child(root, node2);
    add_child(root, node3);
    add_child(node1, node4);
    add_child(node1, node5);
    add_child(node2, node6);
    add_child(node2, node7);
    add_child(node3, node8);
    add_child(node3, node9);

    reparent(node6, NULL);
    reparent(node2, node6);
    reparent(node7, node2);
    reparent(root, node2);

    return 0;
}