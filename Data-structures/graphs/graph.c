#include <stdio.h>
#include <stdlib.h>

// Define a structure for an adjacency list node
typedef struct AdjListNode {
    int dest;                       // Destination vertex of the edge
    struct AdjListNode* next;       // Pointer to the next node
} AdjListNode;

// Define a structure for an adjacency list
typedef struct AdjList {
    AdjListNode* head;              // Pointer to the head node of the list
} AdjList;

// Define a structure for the graph
typedef struct Graph {
    int V;                          // Number of vertices in the graph
    AdjList* array;                 // Array of adjacency lists
} Graph;

// Function to create a new adjacency list node
AdjListNode* createAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    graph->V = V;

    // Create an array of adjacency lists
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    if (graph->array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(graph);
        return NULL;
    }

    // Initialize each adjacency list as empty by making head NULL
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    AdjListNode* newNode = createAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = createAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the adjacency list representation of the graph
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Function to free the memory of the graph
void freeGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        AdjListNode* current = graph->array[v].head;
        while (current != NULL) {
            AdjListNode* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->array);
    free(graph);
}

// Main function to test the graph implementation
int main() {
    int V = 5;
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printGraph(graph);

    freeGraph(graph);

    return EXIT_SUCCESS;
}
