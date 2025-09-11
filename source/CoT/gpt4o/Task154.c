#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct {
    int nodes[MAX_NODES];
    int size;
} IntArray;

typedef struct {
    IntArray edges[MAX_NODES];
} Graph;

void add_edge(Graph* graph, int node, int neighbor) {
    graph->edges[node].nodes[graph->edges[node].size++] = neighbor;
}

IntArray depthFirstSearch(Graph* graph, int start) {
    IntArray result = { .size = 0 };
    int visited[MAX_NODES] = {0};
    int stack[MAX_NODES];
    int top = -1;
    
    stack[++top] = start;

    while (top != -1) {
        int node = stack[top--];
        if (!visited[node]) {
            visited[node] = 1;
            result.nodes[result.size++] = node;
            for (int i = 0; i < graph->edges[node].size; ++i) {
                int neighbor = graph->edges[node].nodes[i];
                stack[++top] = neighbor;
            }
        }
    }
    
    return result;
}

void print_result(IntArray result) {
    for (int i = 0; i < result.size; ++i) {
        printf("%d ", result.nodes[i]);
    }
    printf("\n");
}

int main() {
    Graph graph = {0};

    add_edge(&graph, 0, 1);
    add_edge(&graph, 0, 2);
    add_edge(&graph, 1, 0);
    add_edge(&graph, 1, 3);
    add_edge(&graph, 1, 4);
    add_edge(&graph, 2, 0);
    add_edge(&graph, 2, 5);
    add_edge(&graph, 3, 1);
    add_edge(&graph, 4, 1);
    add_edge(&graph, 4, 5);
    add_edge(&graph, 5, 2);
    add_edge(&graph, 5, 4);

    IntArray result1 = depthFirstSearch(&graph, 0);
    IntArray result2 = depthFirstSearch(&graph, 1);
    IntArray result3 = depthFirstSearch(&graph, 2);
    IntArray result4 = depthFirstSearch(&graph, 3);
    IntArray result5 = depthFirstSearch(&graph, 4);

    print_result(result1);
    print_result(result2);
    print_result(result3);
    print_result(result4);
    print_result(result5);

    return 0;
}