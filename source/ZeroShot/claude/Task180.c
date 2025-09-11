
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 1000
#define MAX_CHILDREN 100

typedef struct Node {
    int value;
    struct Node* children[MAX_CHILDREN];
    int childCount;
} Node;

typedef struct {
    int values[MAX_NODES];
    int count;
} Queue;

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->childCount = 0;
    return node;
}

void buildGraph(Node* node, int parent, int graph[][MAX_NODES], int* graphSize) {
    if (parent != -1) {
        graph[node->value][parent] = 1;
        graph[parent][node->value] = 1;
    }
    
    for (int i = 0; i < node->childCount; i++) {
        buildGraph(node->children[i], node->value, graph, graphSize);
        if (node->children[i]->value > *graphSize) {
            *graphSize = node->children[i]->value;
        }
    }
}

Node* reparentTree(Node* root, int newRootValue) {
    int graph[MAX_NODES][MAX_NODES] = {0};
    int graphSize = root->value;
    buildGraph(root, -1, graph, &graphSize);
    graphSize++;
    
    // BFS implementation
    Queue queue = {{newRootValue}, 1};
    bool visited[MAX_NODES] = {false};
    Node* nodes[MAX_NODES];
    
    Node* newRoot = createNode(newRootValue);
    nodes[newRootValue] = newRoot;
    visited[newRootValue] = true;
    
    while (queue.count > 0) {
        // Pop from queue
        int current = queue.values[0];
        for (int i = 0; i < queue.count - 1; i++) {
            queue.values[i] = queue.values[i + 1];
        }
        queue.count--;
        
        Node* currentNode = nodes[current];
        
        for (int neighbor = 0; neighbor < graphSize; neighbor++) {
            if (graph[current][neighbor] && !visited[neighbor]) {
                Node* newNode = createNode(neighbor);
                currentNode->children[currentNode->childCount++] = newNode;
                nodes[neighbor] = newNode;
                
                // Push to queue
                queue.values[queue.count++] = neighbor;
                visited[neighbor] = true;
            }
        }
    }
    
    return newRoot;
}

void printTree(Node* node, char* prefix, bool isLast) {
    printf("%s%s%d\\n", prefix, isLast ? "└── " : "├── ", node->value);
    
    char newPrefix[1000];
    sprintf(newPrefix, "%s%s", prefix, isLast ? "    " : "│   ");
    
    for (int i = 0; i < node->childCount; i++) {
        printTree(node->children[i], newPrefix, i == node->childCount - 1);
    }
}

int main() {
    // Test case 1: Simple tree
    Node* root1 = createNode(0);
    root1->children[root1->childCount++] = createNode(1);
    root1->children[root1->childCount++] = createNode(2);
    Node* newRoot1 = reparentTree(root1, 2);
    printf("Test case 1:\\n");
    printTree(newRoot1, "", true);
    
    // Test case 2: Larger tree
    Node* root2 = createNode(0);
    root2->children[root2->childCount++] = createNode(1);
    root2->children[root2->childCount++] = createNode(2);
    root2->children[root2->childCount++] = createNode(3);
    root2->children[0]->children[root2->children[0]->childCount++] = createNode(4);
    root2->children[0]->children[root2->children[0]->childCount++] = createNode(5);
    Node* newRoot2 = reparentTree(root2, 4);
    printf("\\nTest case 2:\\n");
    printTree(newRoot2, "", true);
    
    return 0;
}
