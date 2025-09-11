
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 1000
#define MAX_EDGES 1000

typedef struct {
    int nodes[MAX_NODES][MAX_NODES];
    int size;
} Graph;

void bfs(const Graph* graph, int start) {
    if (graph == NULL || graph->size <= 0) {
        return;
    }
    
    bool visited[MAX_NODES] = {false};
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    
    queue[rear++] = start;
    visited[start] = true;
    
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);
        
        for (int i = 0; i < graph->size; i++) {
            if (graph->nodes[current][i] && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
}

void addEdge(Graph* graph, int src, int dest) {
    if (src >= 0 && src < graph->size && dest >= 0 && dest < graph->size) {
        graph->nodes[src][dest] = 1;
    }
}

int main() {
    // Test case 1
    Graph graph1 = {0};
    graph1.size = 4;
    addEdge(&graph1, 0, 1);
    addEdge(&graph1, 0, 2);
    addEdge(&graph1, 1, 2);
    addEdge(&graph1, 2, 0);
    addEdge(&graph1, 2, 3);
    addEdge(&graph1, 3, 3);
    printf("Test 1: ");
    bfs(&graph1, 2);
    printf("\\n");
    
    // Test case 2
    Graph graph2 = {0};
    graph2.size = 7;
    addEdge(&graph2, 1, 2);
    addEdge(&graph2, 1, 3);
    addEdge(&graph2, 1, 4);
    addEdge(&graph2, 2, 1);
    addEdge(&graph2, 2, 5);
    addEdge(&graph2, 3, 1);
    addEdge(&graph2, 3, 6);
    addEdge(&graph2, 4, 1);
    addEdge(&graph2, 5, 2);
    addEdge(&graph2, 6, 3);
    printf("Test 2: ");
    bfs(&graph2, 1);
    printf("\\n");
    
    // Test case 3
    Graph graph3 = {0};
    printf("Test 3: ");
    bfs(&graph3, 1);
    printf("\\n");
    
    // Test case 4
    Graph graph4 = {0};
    graph4.size = 6;
    addEdge(&graph4, 1, 2);
    addEdge(&graph4, 2, 3);
    addEdge(&graph4, 3, 4);
    addEdge(&graph4, 4, 5);
    printf("Test 4: ");
    bfs(&graph4, 1);
    printf("\\n");
    
    // Test case 5
    Graph graph5 = {0};
    graph5.size = 8;
    addEdge(&graph5, 1, 2);
    addEdge(&graph5, 1, 3);
    addEdge(&graph5, 2, 4);
    addEdge(&graph5, 2, 5);
    addEdge(&graph5, 3, 6);
    addEdge(&graph5, 3, 7);
    printf("Test 5: ");
    bfs(&graph5, 1);
    printf("\\n");
    
    return 0;
}
