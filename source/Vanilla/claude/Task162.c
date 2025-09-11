
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 1000

struct Edge {
    int dest;
    int weight;
};

struct Graph {
    struct Edge* edges[MAX_VERTICES];
    int edge_count[MAX_VERTICES];
};

int* dijkstra(struct Graph* graph, int start, int V) {
    int* dist = (int*)malloc(V * sizeof(int));
    bool* visited = (bool*)malloc(V * sizeof(bool));
    
    for(int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    
    dist[start] = 0;
    
    for(int count = 0; count < V-1; count++) {
        int min = INT_MAX;
        int min_index = -1;
        
        for(int v = 0; v < V; v++) {
            if(!visited[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }
        
        if(min_index == -1) break;
        
        visited[min_index] = true;
        
        for(int i = 0; i < graph->edge_count[min_index]; i++) {
            int v = graph->edges[min_index][i].dest;
            int weight = graph->edges[min_index][i].weight;
            
            if(!visited[v] && dist[min_index] != INT_MAX && 
               dist[min_index] + weight < dist[v]) {
                dist[v] = dist[min_index] + weight;
            }
        }
    }
    
    free(visited);
    return dist;
}

int main() {
    // Test Case 1
    struct Graph graph1 = {0};
    graph1.edges[0] = (struct Edge*)malloc(2 * sizeof(struct Edge));
    graph1.edges[0][0] = (struct Edge){1, 1};
    graph1.edges[0][1] = (struct Edge){2, 4};
    graph1.edge_count[0] = 2;
    
    graph1.edges[1] = (struct Edge*)malloc(2 * sizeof(struct Edge));
    graph1.edges[1][0] = (struct Edge){2, 2};
    graph1.edges[1][1] = (struct Edge){3, 5};
    graph1.edge_count[1] = 2;
    
    graph1.edges[2] = (struct Edge*)malloc(1 * sizeof(struct Edge));
    graph1.edges[2][0] = (struct Edge){3, 1};
    graph1.edge_count[2] = 1;
    
    int* result1 = dijkstra(&graph1, 0, 4);
    for(int i = 0; i < 4; i++) printf("%d ", result1[i]);
    printf("\\n");
    
    // Free memory
    for(int i = 0; i < 3; i++) {
        free(graph1.edges[i]);
    }
    free(result1);
    
    // Test Case 2
    struct Graph graph2 = {0};
    graph2.edges[0] = (struct Edge*)malloc(1 * sizeof(struct Edge));
    graph2.edges[0][0] = (struct Edge){1, 2};
    graph2.edge_count[0] = 1;
    
    graph2.edges[1] = (struct Edge*)malloc(1 * sizeof(struct Edge));
    graph2.edges[1][0] = (struct Edge){2, 3};
    graph2.edge_count[1] = 1;
    
    int* result2 = dijkstra(&graph2, 0, 3);
    for(int i = 0; i < 3; i++) printf("%d ", result2[i]);
    printf("\\n");
    
    // Free memory
    for(int i = 0; i < 2; i++) {
        free(graph2.edges[i]);
    }
    free(result2);
    
    return 0;
}
