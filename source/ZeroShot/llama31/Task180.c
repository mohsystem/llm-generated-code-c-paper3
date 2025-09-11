#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* parent;
    struct Node** children;
    int childrenCount;
} Node;

Node* createNode(int value) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->parent = NULL;
    node->children = NULL;
    node->childrenCount = 0;
    return node;
}

void addChild(Node* parent, Node* child) {
    parent->children = realloc(parent->children, (parent->childrenCount + 1) * sizeof(Node*));
    parent->children[parent->childrenCount++] = child;
    child->parent = parent;
}

void reparentFromNode(Node* root, Node* newRoot) {
    if (root == newRoot) return;

    Node* current = root;
    Node* newParent = NULL;

    while (current != newRoot) {
        newParent = current->parent;
        current->parent = NULL;
        if (newParent != NULL) {
            for (int i = 0; i < newParent->childrenCount; ++i) {
                if (newParent->children[i] == current) {
                    // Remove current from newParent's children
                    newParent->childrenCount--;
                    for (int j = i; j < newParent->childrenCount; ++j) {
                        newParent->children[j] = newParent->children[j + 1];
                    }
                    newParent->children = realloc(newParent->children, newParent->childrenCount * sizeof(Node*));
                    break;
                }
            }
        }
        current = newParent;
    }

    reattachChildren(root, newRoot);
}

void reattachChildren(Node* root, Node* newRoot) {
    if (root == newRoot) return;

    for (int i = 0; i < root->childrenCount; ++i) {
        reattachChildren(root->children[i], newRoot);
    }

    if (root->parent != NULL) {
        for (int i = 0; i < root->parent->childrenCount; ++i) {
            if (root->parent->children[i] == root) {
                // Remove root from parent's children
                root->parent->childrenCount--;
                for (int j = i; j < root->parent->childrenCount; ++j) {
                    root->parent->children[j] = root->parent->children[j + 1];
                }
                root->parent->children = realloc(root->parent->children, root->parent->childrenCount * sizeof(Node*));
                break;
            }
        }
        root->parent = NULL;
    }

    addChild(newRoot, root);
}

void printTree(Node* node, int level) {
    for (int i = 0; i < level; ++i) {
        printf("  ");
    }
    printf("%d\n", node->value);
    for (int i = 0; i < node->childrenCount; ++i) {
        printTree(node->children[i], level + 1);
    }
}

int main() {
    // Create a sample tree
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

    // Reparent the tree from node 6's perspective
    reparentFromNode(root, node6);

    printf("Tree reparented from node 6's perspective:\n");
    printTree(node6, 0);

    return 0;
}