#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node** children;
    int childrenCount;
    struct Node* parent;
} Node;

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->children = NULL;
    node->childrenCount = 0;
    node->parent = NULL;
    return node;
}

void addChild(Node* parent, Node* child) {
    child->parent = parent;
    parent->childrenCount++;
    parent->children = (Node**)realloc(parent->children, parent->childrenCount * sizeof(Node*));
    parent->children[parent->childrenCount - 1] = child;
}

void reparent(Node* root, Node* newRoot) {
    if (root == newRoot) return;

    // Remove newRoot from its current position
    Node* newRootParent = newRoot->parent;
    if (newRootParent != NULL) {
        for (int i = 0; i < newRootParent->childrenCount; i++) {
            if (newRootParent->children[i] == newRoot) {
                newRootParent->children[i] = newRootParent->children[newRootParent->childrenCount - 1];
                newRootParent->childrenCount--;
                newRootParent->children = (Node**)realloc(newRootParent->children, newRootParent->childrenCount * sizeof(Node*));
                break;
            }
        }
    }

    // Make newRoot the new root
    newRoot->parent = NULL;

    // Reparent the rest of the tree
    Node* current = root;
    while (current != newRoot) {
        Node* next = current->parent;
        current->parent = newRoot;
        newRoot->childrenCount++;
        newRoot->children = (Node**)realloc(newRoot->children, newRoot->childrenCount * sizeof(Node*));
        newRoot->children[newRoot->childrenCount - 1] = current;
        current = next;
    }
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
    // Create the tree
    Node* root = createNode(0);
    Node* node1 = createNode(1);
    Node* node2 = createNode(2);
    Node* node3 = createNode(3);
    Node* node4 = createNode(4);
    Node* node5 = createNode(5);
    Node* node6 = createNode(6);
    Node* node7 = createNode(7);
    Node* node8 = createNode(8);
    Node* node9 = createNode(9);

    addChild(root, node1);
    addChild(root, node2);
    addChild(root, node3);
    addChild(node1, node4);
    addChild(node1, node5);
    addChild(node2, node6);
    addChild(node2, node7);
    addChild(node3, node8);
    addChild(node3, node9);

    printf("Original Tree:\n");
    printTree(root, 0);

    // Reparent the tree from node6's perspective
    reparent(root, node6);

    printf("Reparented Tree from node6's perspective:\n");
    printTree(node6, 0);

    return 0;
}