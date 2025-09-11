
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100
#define MAX_CHILDREN 10

typedef struct Node {
    int value;
    struct Node* children[MAX_CHILDREN];
    int childCount;
} Node;

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->childCount = 0;
    return node;
}

Node* buildTree(Node** nodes, int connections[][MAX_NODES], int nodeCount, 
                int current, bool* visited) {
    visited[current] = true;
    Node* currentNode = nodes[current];
    
    // Process direct connections
    for (int i = 0; i < nodeCount; i++) {
        if (connections[current][i] && !visited[i]) {
            currentNode->children[currentNode->childCount++] = 
                buildTree(nodes, connections, nodeCount, i, visited);
        }
    }
    
    // Process reverse connections
    for (int i = 0; i < nodeCount; i++) {
        if (connections[i][current] && !visited[i]) {
            currentNode->children[currentNode->childCount++] = 
                buildTree(nodes, connections, nodeCount, i, visited);
        }
    }
    
    return currentNode;
}

Node* reparent(int connections[][MAX_NODES], int nodeCount, int root) {
    Node** nodes = (Node**)malloc(nodeCount * sizeof(Node*));
    bool* visited = (bool*)calloc(nodeCount, sizeof(bool));
    
    if (nodes == NULL || visited == NULL) {
        free(nodes);
        free(visited);
        return NULL;
    }
    
    // Create nodes
    for (int i = 0; i < nodeCount; i++) {
        nodes[i] = createNode(i);
        if (nodes[i] == NULL) {
            // Clean up on failure
            for (int j = 0; j < i; j++) {
                free(nodes[j]);
            }
            free(nodes);
            free(visited);
            return NULL;
        }
    }
    
    Node* result = buildTree(nodes, connections, nodeCount, root, visited);
    
    // Clean up
    free(visited);
    free(nodes);
    
    return result;
}

void freeTree(Node* root) {
    if (root == NULL) return;
    for (int i = 0; i < root->childCount; i++) {
        freeTree(root->children[i]);
    }
    free(root);
}

int main() {
    // Test cases
    int nodeCount = 10;
    int connections[MAX_NODES][MAX_NODES] = {0};
    
    // Define connections for the example tree
    connections[0][1] = connections[1][0] = 1;
    connections[0][2] = connections[2][0] = 1;
    connections[0][3] = connections[3][0] = 1;
    connections[1][4] = connections[4][1] = 1;
    connections[1][5] = connections[5][1] = 1;
    connections[2][6] = connections[6][2] = 1;
    connections[2][7] = connections[7][2] = 1;
    connections[3][8] = connections[8][3] = 1;
    connections[3][9] = connections[9][3] = 1;
    
    // Test case 1: Reparent from node 6
    Node* result1 = reparent(connections, nodeCount, 6);
    printf("Test 1: Reparented from node 6\\n");
    freeTree(result1);
    
    // Test case 2: Reparent from node 0
    Node* result2 = reparent(connections, nodeCount, 0);
    printf("Test 2: Reparented from node 0\\n");
    freeTree(result2);
    
    // Test case 3: Reparent from node 9
    Node* result3 = reparent(connections, nodeCount, 9);
    printf("Test 3: Reparented from node 9\\n");
    freeTree(result3);
    
    // Test case 4: Reparent from node 2
    Node* result4 = reparent(connections, nodeCount, 2);
    printf("Test 4: Reparented from node 2\\n");
    freeTree(result4);
    
    // Test case 5: Reparent from node 4
    Node* result5 = reparent(connections, nodeCount, 4);
    printf("Test 5: Reparented from node 4\\n");
    freeTree(result5);
    
    return 0;
}
