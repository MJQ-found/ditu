#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_adj_list.h"

void createGraph(GraphAdjList *graph, int directed) {
    int i;
    graph->vertexNum = 0;
    graph->edgeNum = 0;
    graph->directed = directed;
    for (i = 0; i < MAX_VERTEX_NUM; i++) {
        graph->adjList[i].name[0] = '\0';
        graph->adjList[i].firstEdge = NULL;
    }
}

int findVertexIndex(GraphAdjList *graph, const char *name) {
    int i;
    for (i = 0; i < graph->vertexNum; i++) {
        if (strcmp(graph->adjList[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int addVertex(GraphAdjList *graph, const char *name) {
    if (graph->vertexNum >= MAX_VERTEX_NUM) {
        printf("Error: 顶点数量已达到最大值!\n");
        return -1;
    }
    if (findVertexIndex(graph, name) != -1) {
        printf("Error: 景点 '%s' 已存在!\n", name);
        return -1;
    }
    strcpy(graph->adjList[graph->vertexNum].name, name);
    graph->adjList[graph->vertexNum].firstEdge = NULL;
    graph->vertexNum++;
    printf("Success: 添加景点 '%s'\n", name);
    return graph->vertexNum - 1;
}

int addEdge(GraphAdjList *graph, const char *fromName, const char *toName, int weight) {
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
    
    EdgeNode *newEdge = (EdgeNode *)malloc(sizeof(EdgeNode));
    if (newEdge == NULL) {
        printf("Error: 内存分配失败!\n");
        return -1;
    }
    newEdge->adjVertex = toIndex;
    newEdge->weight = weight;
    newEdge->nextEdge = graph->adjList[fromIndex].firstEdge;
    graph->adjList[fromIndex].firstEdge = newEdge;
    
    if (!graph->directed) {
        EdgeNode *reverseEdge = (EdgeNode *)malloc(sizeof(EdgeNode));
        if (reverseEdge == NULL) {
            printf("Error: 内存分配失败!\n");
            return -1;
        }
        reverseEdge->adjVertex = fromIndex;
        reverseEdge->weight = weight;
        reverseEdge->nextEdge = graph->adjList[toIndex].firstEdge;
        graph->adjList[toIndex].firstEdge = reverseEdge;
    }
    
    graph->edgeNum++;
    printf("Success: 添加路径 '%s' -> '%s' (距离: %d)\n", fromName, toName, weight);
    return 0;
}

void displayGraph(GraphAdjList *graph) {
    int i;
    EdgeNode *p;
    
    printf("\n=== 景区路径图 (邻接表) ===\n");
    printf("景点数量: %d, 路径数量: %d\n", graph->vertexNum, graph->edgeNum);
    
    for (i = 0; i < graph->vertexNum; i++) {
        printf("%d. %s -> ", i, graph->adjList[i].name);
        p = graph->adjList[i].firstEdge;
        if (p == NULL) {
            printf("(无相邻景点)");
        }
        while (p != NULL) {
            printf("%s(%d)", graph->adjList[p->adjVertex].name, p->weight);
            p = p->nextEdge;
            if (p != NULL) {
                printf(" -> ");
            }
        }
        printf("\n");
    }
    printf("============================\n");
}

void displayVertexList(GraphAdjList *graph) {
    int i;
    
    printf("\n=== 景点链表 ===\n");
    printf("序号\t景点名称\n");
    printf("----------------\n");
    for (i = 0; i < graph->vertexNum; i++) {
        printf("%d\t%s\n", i, graph->adjList[i].name);
    }
    printf("----------------\n");
    printf("总计: %d 个景点\n", graph->vertexNum);
    printf("================\n");
}

void destroyGraph(GraphAdjList *graph) {
    int i;
    EdgeNode *p, *q;
    
    for (i = 0; i < graph->vertexNum; i++) {
        p = graph->adjList[i].firstEdge;
        while (p != NULL) {
            q = p->nextEdge;
            free(p);
            p = q;
        }
        graph->adjList[i].firstEdge = NULL;
    }
    graph->vertexNum = 0;
    graph->edgeNum = 0;
}