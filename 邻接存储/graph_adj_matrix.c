#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_adj_matrix.h"

void createGraph(GraphAdjMatrix *graph, int directed) {
    int i, j;
    graph->vertexNum = 0;
    graph->edgeNum = 0;
    graph->directed = directed;
    for (i = 0; i < MAX_VERTEX_NUM; i++) {
        graph->name[i][0] = '\0';
        for (j = 0; j < MAX_VERTEX_NUM; j++) {
            graph->adjMatrix[i][j] = INF;
        }
        graph->adjMatrix[i][i] = 0;
    }
}

int findVertexIndex(GraphAdjMatrix *graph, const char *name) {
    int i;
    for (i = 0; i < graph->vertexNum; i++) {
        if (strcmp(graph->name[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

int addVertex(GraphAdjMatrix *graph, const char *name) {
    if (graph->vertexNum >= MAX_VERTEX_NUM) {
        printf("Error: 顶点数量已达到最大值!\n");
        return -1;
    }
    if (findVertexIndex(graph, name) != -1) {
        printf("Error: 景点 '%s' 已存在!\n", name);
        return -1;
    }
    strcpy(graph->name[graph->vertexNum], name);
    graph->vertexNum++;
    printf("Success: 添加景点 '%s'\n", name);
    return graph->vertexNum - 1;
}

int addEdge(GraphAdjMatrix *graph, const char *fromName, const char *toName, int weight) {
    int fromIndex = findVertexIndex(graph, fromName);
    int toIndex = findVertexIndex(graph, toName);
    
    if (fromIndex == -1) {
        printf("Error: 起点 '%s' 不存在!\n", fromName);
        return -1;
    }
    if (toIndex == -1) {
        printf("Error: 终点 '%s' 不存在!\n", toName);
        return -1;
    }
    
    graph->adjMatrix[fromIndex][toIndex] = weight;
    
    if (!graph->directed) {
        graph->adjMatrix[toIndex][fromIndex] = weight;
    }
    
    graph->edgeNum++;
    printf("Success: 添加路径 '%s' -> '%s' (距离: %d)\n", fromName, toName, weight);
    return 0;
}

void displayGraph(GraphAdjMatrix *graph) {
    int i, j;
    
    printf("\n=== 景区路径图 (邻接矩阵) ===\n");
    printf("景点数量: %d, 路径数量: %d\n", graph->vertexNum, graph->edgeNum);
    
    printf("\n   ");
    for (i = 0; i < graph->vertexNum; i++) {
        printf("%-8s", graph->name[i]);
    }
    printf("\n");
    
    for (i = 0; i < graph->vertexNum; i++) {
        printf("%-4s", graph->name[i]);
        for (j = 0; j < graph->vertexNum; j++) {
            if (graph->adjMatrix[i][j] == INF) {
                printf("%-8s", "∞");
            } else {
                printf("%-8d", graph->adjMatrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("==============================\n");
}

void displayVertexList(GraphAdjMatrix *graph) {
    int i;
    
    printf("\n=== 景点链表 ===\n");
    printf("序号\t景点名称\n");
    printf("----------------\n");
    for (i = 0; i < graph->vertexNum; i++) {
        printf("%d\t%s\n", i, graph->name[i]);
    }
    printf("----------------\n");
    printf("总计: %d 个景点\n", graph->vertexNum);
    printf("================\n");
}

void destroyGraph(GraphAdjMatrix *graph) {
    int i;
    for (i = 0; i < graph->vertexNum; i++) {
        graph->name[i][0] = '\0';
    }
    graph->vertexNum = 0;
    graph->edgeNum = 0;
}