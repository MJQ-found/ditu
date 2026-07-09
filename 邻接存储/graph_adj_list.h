#ifndef GRAPH_ADJ_LIST_H
#define GRAPH_ADJ_LIST_H

#define MAX_VERTEX_NUM 50
#define MAX_NAME_LEN 50

typedef struct EdgeNode {
    int adjVertex;
    int weight;
    struct EdgeNode *nextEdge;
} EdgeNode;

typedef struct VertexNode {
    char name[MAX_NAME_LEN];
    EdgeNode *firstEdge;
} VertexNode;

typedef struct {
    VertexNode adjList[MAX_VERTEX_NUM];
    int vertexNum;
    int edgeNum;
    int directed;
} GraphAdjList;

void createGraph(GraphAdjList *graph, int directed);
int addVertex(GraphAdjList *graph, const char *name);
int addEdge(GraphAdjList *graph, const char *fromName, const char *toName, int weight);
void displayGraph(GraphAdjList *graph);
void displayVertexList(GraphAdjList *graph);
void destroyGraph(GraphAdjList *graph);
int findVertexIndex(GraphAdjList *graph, const char *name);

#endif