#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* parent;
    struct Node** children;
    int childrenCount;
} Node;

void addChild(Node* parent, Node* child) {
    parent->children = realloc(parent->children, (parent->childrenCount + 1) * sizeof(Node*));
    parent->children[parent->childrenCount++] = child;
    child->parent = parent;
}

void reparent(Node* node, Node* newParent) {
    if (node->parent) {
        for (int i = 0; i < node->parent->childrenCount; i++) {
            if (node->parent->children[i] == node) {
                for (int j = i; j < node->parent->childrenCount - 1; j++) {
                    node->parent->children[j] = node->parent->children[j + 1];
                }
                node->parent->childrenCount--;
                node->parent->children = realloc(node->parent->children, node->parent->childrenCount * sizeof(Node*));
                break;
            }
        }
    }
    addChild(newParent, node);
}

void printTree(Node* node, int level) {
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%d\n", node->value);
    for (int i = 0; i < node->childrenCount; i++) {
        printTree(node->children[i], level + 1);
    }
}

int main() {
    // Create a sample tree
    Node* root = malloc(sizeof(Node));
    root->value = 0;
    root->parent = NULL;
    root->children = NULL;
    root->childrenCount = 0;

    Node* node1 = malloc(sizeof(Node));
    node1->value = 1;
    node1->parent = NULL;
    node1->children = NULL;
    node1->childrenCount = 0;

    Node* node2 = malloc(sizeof(Node));
    node2->value = 2;
    node2->parent = NULL;
    node2->children = NULL;
    node2->childrenCount = 0;

    Node* node3 = malloc(sizeof(Node));
    node3->value = 3;
    node3->parent = NULL;
    node3->children = NULL;
    node3->childrenCount = 0;

    Node* node4 = malloc(sizeof(Node));
    node4->value = 4;
    node4->parent = NULL;
    node4->children = NULL;
    node4->childrenCount = 0;

    Node* node5 = malloc(sizeof(Node));
    node5->value = 5;
    node5->parent = NULL;
    node5->children = NULL;
    node5->childrenCount = 0;

    Node* node6 = malloc(sizeof(Node));
    node6->value = 6;
    node6->parent = NULL;
    node6->children = NULL;
    node6->childrenCount = 0;

    Node* node7 = malloc(sizeof(Node));
    node7->value = 7;
    node7->parent = NULL;
    node7->children = NULL;
    node7->childrenCount = 0;

    Node* node8 = malloc(sizeof(Node));
    node8->value = 8;
    node8->parent = NULL;
    node8->children = NULL;
    node8->childrenCount = 0;

    Node* node9 = malloc(sizeof(Node));
    node9->value = 9;
    node9->parent = NULL;
    node9->children = NULL;
    node9->childrenCount = 0;

    addChild(root, node1);
    addChild(root, node2);
    addChild(root, node3);
    addChild(node1, node4);
    addChild(node1, node5);
    addChild(node2, node6);
    addChild(node2, node7);
    addChild(node3, node8);
    addChild(node3, node9);

    // Print original tree
    printf("Original Tree:\n");
    printTree(root, 0);

    // Reparent tree from node 6's perspective
    reparent(node2, node6);
    reparent(root, node6);
    reparent(node3, node6);

    // Print reparented tree
    printf("Reparented Tree from node 6's perspective:\n");
    printTree(node6, 0);

    return 0;
}