// Recursive function for DFS traversal from a given vertex
void DFSUtil(Graph* graph, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("%d ", vertex);

    // Recur for all the vertices adjacent to this vertex
    AdjListNode* temp = graph->array[vertex].head;
    while (temp) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

// Function to perform DFS traversal from a given source vertex
void DFS(Graph* graph, int startVertex) {
    // Create a boolean array to mark visited vertices
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++) {
        visited[i] = false;
    }

    // Call the recursive helper function to perform DFS
    DFSUtil(graph, startVertex, visited);

    free(visited);
}