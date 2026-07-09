#ifndef GRAPH_ADJ_MATRIX_H
#define GRAPH_ADJ_MATRIX_H

#define MAX_VERTEX_NUM 50
#define MAX_NAME_LEN 50
#define INF 99999

typedef struct {
    char name[MAX_VERTEX_NUM][MAX_NAME_LEN];
    int adjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vertexNum;
    int edgeNum;
    int directed;
} GraphAdjMatrix;

void createGraph(GraphAdjMatrix *graph, int directed);
int addVertex(GraphAdjMatrix *graph, const char *name);
int addEdge(GraphAdjMatrix *graph, const char *fromName, const char *toName, int weight);
void displayGraph(GraphAdjMatrix *graph);
void displayVertexList(GraphAdjMatrix *graph);
void destroyGraph(GraphAdjMatrix *graph);
int findVertexIndex(GraphAdjMatrix *graph, const char *name);

#endif