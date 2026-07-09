#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <stdbool.h>

#define MAX_VERTEX_NUM 20

typedef struct EdgeNode {
    int adjVertex;
    int weight;
    struct EdgeNode* next;
} EdgeNode;

typedef struct {
    char data;
    EdgeNode* firstEdge;
} VertexNode;

typedef struct {
    VertexNode vertices[MAX_VERTEX_NUM];
    int vertexCount;
    int edgeCount;
    bool directed;
} AdjacencyList;

AdjacencyList* al_create(bool directed);
void al_destroy(AdjacencyList* graph);
int al_addVertex(AdjacencyList* graph, char data);
int al_removeVertex(AdjacencyList* graph, int index);
int al_updateVertex(AdjacencyList* graph, int index, char newData);
int al_findVertex(AdjacencyList* graph, char data);
char al_getVertex(AdjacencyList* graph, int index);
int al_addEdge(AdjacencyList* graph, int from, int to, int weight);
int al_removeEdge(AdjacencyList* graph, int from, int to);
int al_updateEdge(AdjacencyList* graph, int from, int to, int newWeight);
int al_getEdge(AdjacencyList* graph, int from, int to);
void al_print(AdjacencyList* graph);
void al_dfs(AdjacencyList* graph, int start);
void al_bfs(AdjacencyList* graph, int start);

#endif
//