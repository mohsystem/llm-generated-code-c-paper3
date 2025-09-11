#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node** children;
    int numChildren;
} Node;

Node* createNode(int value, int numChildren, Node** children) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->children = children;
    node->numChildren = numChildren;
    return node;
}

Node* reparentTree(Node* root, int newNodeValue) {
    if (root == NULL) return NULL;
    if (root->value == newNodeValue) return root;

    Node* newRoot = NULL;
    for (int i = 0; i < root->numChildren; ++i) {
        Node* result = reparentTree(root->children[i], newNodeValue);
        if (result != NULL) {
            newRoot = result;
            // Adjust the children of the old root
            Node** newChildren = malloc((root->numChildren - 1) * sizeof(Node*));
            int j = 0;
            for (int k = 0; k < root->numChildren; ++k) {
                if (k != i) {
                    newChildren[j++] = root->children[k];
                }
            }
            free(root->children);
            root->children = newChildren;
            root->numChildren = j;
            // Add the old root to the children of the new root
            Node** newNewChildren = malloc((newRoot->numChildren + 1) * sizeof(Node*));
            for (int k = 0; k < newRoot->numChildren; ++k) {
                newNewChildren[k] = newRoot->children[k];
            }
            newNewChildren[newRoot->numChildren] = root;
            free(newRoot->children);
            newRoot->children = newNewChildren;
            newRoot->numChildren++;
            break;
        }
    }
    return newRoot;
}

void printTree(Node* node, int level) {
    if (node == NULL) return;
    for (int i = 0; i < level; ++i) printf("  ");
    printf("%d\n", node->value);
    for (int i = 0; i < node->numChildren; ++i) {
        printTree(node->children[i], level + 1);
    }
}

int main() {
    // Example tree
    Node* root = createNode(0, 3, (Node*[]) {
        createNode(1, 2, (Node*[]) { createNode(4, 0, NULL), createNode(5, 0, NULL) }),
        createNode(2, 2, (Node*[]) { createNode(6, 0, NULL), createNode(7, 0, NULL) }),
        createNode(3, 2, (Node*[]) { createNode(8, 0, NULL), createNode(9, 0, NULL) })
    });

    printf("Original Tree:\n");
    printTree(root, 0);

    Node* newRoot = reparentTree(root, 6);

    printf("Reparented Tree from node 6:\n");
    printTree(newRoot, 0);

    return 0;
}