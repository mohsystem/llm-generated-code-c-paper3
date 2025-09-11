
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct Node {
    int value;
    struct Node** children;
    int childCount;
    int childCapacity;
    struct Node* parent;
} Node;

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->childCapacity = 4;
    node->childCount = 0;
    node->children = (Node**)malloc(sizeof(Node*) * node->childCapacity);
    node->parent = NULL;
    return node;
}

void addChild(Node* parent, Node* child) {
    if (parent->childCount >= parent->childCapacity) {
        parent->childCapacity *= 2;
        parent->children = (Node**)realloc(parent->children, sizeof(Node*) * parent->childCapacity);
    }
    parent->children[parent->childCount++] = child;
    child->parent = parent;
}

void mapNodes(Node* node, Node** nodeMap, int* mapSize) {
    if (!node) return;
    nodeMap[*mapSize] = node;
    (*mapSize)++;
    
    for (int i = 0; i < node->childCount; i++) {
        mapNodes(node->children[i], nodeMap, mapSize);
    }
}

Node* findNode(Node** nodeMap, int mapSize, int value) {
    for (int i = 0; i < mapSize; i++) {
        if (nodeMap[i]->value == value) {
            return nodeMap[i];
        }
    }
    return NULL;
}

void reparent(Node* node, Node* parent, bool* visited, int visitedSize) {
    if (visited[node->value]) return;
    visited[node->value] = true;

    Node** connections = (Node**)malloc(sizeof(Node*) * (node->childCount + 1));
    int connectionCount = 0;

    for (int i = 0; i < node->childCount; i++) {
        connections[connectionCount++] = node->children[i];
    }
    if (node->parent) {
        connections[connectionCount++] = node->parent;
    }

    node->childCount = 0;
    node->parent = parent;

    if (parent) {
        addChild(parent, node);
    }

    for (int i = 0; i < connectionCount; i++) {
        if (connections[i] != parent) {
            reparent(connections[i], node, visited, visitedSize);
        }
    }

    free(connections);
}

Node* reparentTree(Node* root, int newRootValue) {
    Node* nodeMap[MAX_NODES];
    int mapSize = 0;
    mapNodes(root, nodeMap, &mapSize);

    Node* newRoot = findNode(nodeMap, mapSize, newRootValue);
    if (!newRoot) return root;

    bool visited[MAX_NODES] = {false};
    reparent(newRoot, NULL, visited, MAX_NODES);

    return newRoot;
}

int main() {
    // Test case 1: Simple tree
    Node* root = createNode(0);
    Node* n1 = createNode(1);
    Node* n2 = createNode(2);
    addChild(root, n1);
    addChild(root, n2);
    
    Node* newRoot = reparentTree(root, 1);
    printf("New root value: %d\\n", newRoot->value);

    // Test case 2: Complex tree
    Node* root2 = createNode(0);
    n1 = createNode(1);
    n2 = createNode(2);
    Node* n3 = createNode(3);
    Node* n4 = createNode(4);
    Node* n5 = createNode(5);
    Node* n6 = createNode(6);
    Node* n7 = createNode(7);
    Node* n8 = createNode(8);
    Node* n9 = createNode(9);

    addChild(root2, n1);
    addChild(root2, n2);
    addChild(root2, n3);
    addChild(n1, n4);
    addChild(n1, n5);
    addChild(n2, n6);
    addChild(n2, n7);
    addChild(n3, n8);
    addChild(n3, n9);

    newRoot = reparentTree(root2, 6);
    printf("New root value: %d\\n", newRoot->value);

    return 0;
}
