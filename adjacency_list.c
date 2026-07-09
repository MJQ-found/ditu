#include "adjacency_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AdjacencyList* al_create(bool directed) {
    AdjacencyList* graph = (AdjacencyList*)malloc(sizeof(AdjacencyList));
    if (graph == NULL) {
        printf("邻接表内存分配失败\n");
        return NULL;
    }
    int i;
    for (i = 0; i < MAX_VERTEX_NUM; i++) {
        graph->vertices[i].data = '\0';
        graph->vertices[i].firstEdge = NULL;
    }
    graph->vertexCount = 0;
    graph->edgeCount = 0;
    graph->directed = directed;
    return graph;
}

void al_destroy(AdjacencyList* graph) {
    if (graph == NULL) {
        return;
    }
    int i;
    for (i = 0; i < graph->vertexCount; i++) {
        EdgeNode* current = graph->vertices[i].firstEdge;
        while (current != NULL) {
            EdgeNode* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph);
}

int al_addVertex(AdjacencyList* graph, char data) {
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return -1;
    }
    if (graph->vertexCount >= MAX_VERTEX_NUM) {
        printf("错误: 已达到最大顶点容量\n");
        return -1;
    }
    graph->vertices[graph->vertexCount].data = data;
    graph->vertices[graph->vertexCount].firstEdge = NULL;
    return graph->vertexCount++;
}

static void al_removeAllEdges(AdjacencyList* graph, int vertexIndex) {
    EdgeNode* current = graph->vertices[vertexIndex].firstEdge;
    while (current != NULL) {
        EdgeNode* next = current->next;
        free(current);
        current = next;
    }
    graph->vertices[vertexIndex].firstEdge = NULL;
}

static void al_removeEdgeFromOther(AdjacencyList* graph, int vertexIndex) {
    int i;
    for (i = 0; i < graph->vertexCount; i++) {
        if (i == vertexIndex) {
            continue;
        }
        EdgeNode** pp = &graph->vertices[i].firstEdge;
        while (*pp != NULL) {
            if ((*pp)->adjVertex == vertexIndex) {
                EdgeNode* temp = *pp;
                *pp = (*pp)->next;
                free(temp);
                graph->edgeCount--;
                break;
            }
            pp = &(*pp)->next;
        }
    }
}

static void al_updateEdgeIndices(AdjacencyList* graph, int removedIndex) {
    int i;
    for (i = 0; i < graph->vertexCount; i++) {
        EdgeNode* current = graph->vertices[i].firstEdge;
        while (current != NULL) {
            if (current->adjVertex > removedIndex) {
                current->adjVertex--;
            }
            current = current->next;
        }
    }
}

int al_removeVertex(AdjacencyList* graph, int index) {
    int i;
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return -1;
    }
    if (index < 0 || index >= graph->vertexCount) {
        printf("错误: 无效顶点索引 %d\n", index);
        return -1;
    }

    al_removeAllEdges(graph, index);
    al_removeEdgeFromOther(graph, index);

    for (i = index; i < graph->vertexCount - 1; i++) {
        graph->vertices[i] = graph->vertices[i + 1];
    }

    al_updateEdgeIndices(graph, index);

    graph->vertices[graph->vertexCount - 1].data = '\0';
    graph->vertices[graph->vertexCount - 1].firstEdge = NULL;
    graph->vertexCount--;

    return 0;
}

int al_updateVertex(AdjacencyList* graph, int index, char newData) {
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return -1;
    }
    if (index < 0 || index >= graph->vertexCount) {
        printf("错误: 无效顶点索引 %d\n", index);
        return -1;
    }
    graph->vertices[index].data = newData;
    return 0;
}

int al_findVertex(AdjacencyList* graph, char data) {
    int i;
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return -1;
    }
    for (i = 0; i < graph->vertexCount; i++) {
        if (graph->vertices[i].data == data) {
            return i;
        }
    }
    return -1;
}

char al_getVertex(AdjacencyList* graph, int index) {
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return '\0';
    }
    if (index < 0 || index >= graph->vertexCount) {
        printf("错误: 无效顶点索引 %d\n", index);
        return '\0';
    }
    return graph->vertices[index].data;
}

int al_addEdge(AdjacencyList* graph, int from, int to, int weight) {
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return -1;
    }
    if (from < 0 || from >= graph->vertexCount || to < 0 || to >= graph->vertexCount) {
        printf("错误: 无效顶点索引 (%d, %d)\n", from, to);
        return -1;
    }

    int existing = al_getEdge(graph, from, to);
    if (existing != 0) {
        printf("警告: 边 (%d, %d) 已存在，更新权重\n", from, to);
        al_updateEdge(graph, from, to, weight);
        return 0;
    }

    EdgeNode* newEdge = (EdgeNode*)malloc(sizeof(EdgeNode));
    if (newEdge == NULL) {
        printf("边节点内存分配失败\n");
        return -1;
    }
    newEdge->adjVertex = to;
    newEdge->weight = weight;
    newEdge->next = graph->vertices[from].firstEdge;
    graph->vertices[from].firstEdge = newEdge;
    graph->edgeCount++;

    if (!graph->directed && from != to) {
        EdgeNode* reverseEdge = (EdgeNode*)malloc(sizeof(EdgeNode));
        if (reverseEdge == NULL) {
            printf("反向边节点内存分配失败\n");
            return -1;
        }
        reverseEdge->adjVertex = from;
        reverseEdge->weight = weight;
        reverseEdge->next = graph->vertices[to].firstEdge;
        graph->vertices[to].firstEdge = reverseEdge;
        graph->edgeCount++;
    }

    return 0;
}

int al_removeEdge(AdjacencyList* graph, int from, int to) {
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return -1;
    }
    if (from < 0 || from >= graph->vertexCount || to < 0 || to >= graph->vertexCount) {
        printf("错误: 无效顶点索引 (%d, %d)\n", from, to);
        return -1;
    }

    EdgeNode** pp = &graph->vertices[from].firstEdge;
    while (*pp != NULL) {
        if ((*pp)->adjVertex == to) {
            EdgeNode* temp = *pp;
            *pp = (*pp)->next;
            free(temp);
            graph->edgeCount--;

            if (!graph->directed && from != to) {
                EdgeNode** pp2 = &graph->vertices[to].firstEdge;
                while (*pp2 != NULL) {
                    if ((*pp2)->adjVertex == from) {
                        EdgeNode* temp2 = *pp2;
                        *pp2 = (*pp2)->next;
                        free(temp2);
                        graph->edgeCount--;
                        break;
                    }
                    pp2 = &(*pp2)->next;
                }
            }
            return 0;
        }
        pp = &(*pp)->next;
    }

    printf("错误: 边 (%d, %d) 不存在\n", from, to);
    return -1;
}

int al_updateEdge(AdjacencyList* graph, int from, int to, int newWeight) {
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return -1;
    }
    if (from < 0 || from >= graph->vertexCount || to < 0 || to >= graph->vertexCount) {
        printf("错误: 无效顶点索引 (%d, %d)\n", from, to);
        return -1;
    }

    EdgeNode* current = graph->vertices[from].firstEdge;
    while (current != NULL) {
        if (current->adjVertex == to) {
            current->weight = newWeight;
            if (!graph->directed && from != to) {
                EdgeNode* reverse = graph->vertices[to].firstEdge;
                while (reverse != NULL) {
                    if (reverse->adjVertex == from) {
                        reverse->weight = newWeight;
                        break;
                    }
                    reverse = reverse->next;
                }
            }
            return 0;
        }
        current = current->next;
    }

    printf("错误: 边 (%d, %d) 不存在\n", from, to);
    return -1;
}

int al_getEdge(AdjacencyList* graph, int from, int to) {
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return -1;
    }
    if (from < 0 || from >= graph->vertexCount || to < 0 || to >= graph->vertexCount) {
        printf("错误: 无效顶点索引 (%d, %d)\n", from, to);
        return -1;
    }

    EdgeNode* current = graph->vertices[from].firstEdge;
    while (current != NULL) {
        if (current->adjVertex == to) {
            return current->weight;
        }
        current = current->next;
    }
    return 0;
}

void al_print(AdjacencyList* graph) {
    int i;
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return;
    }
    printf("\n邻接表图 (%s):\n", graph->directed ? "有向" : "无向");
    printf("顶点数: %d, 边数: %d\n", graph->vertexCount, graph->edgeCount);
    for (i = 0; i < graph->vertexCount; i++) {
        printf("顶点 %c:", graph->vertices[i].data);
        EdgeNode* current = graph->vertices[i].firstEdge;
        while (current != NULL) {
            printf(" -> %c (%d)", graph->vertices[current->adjVertex].data, current->weight);
            current = current->next;
        }
        printf(" -> NULL\n");
    }
}

static void al_dfsHelper(AdjacencyList* graph, int start, bool* visited) {
    printf("%c ", graph->vertices[start].data);
    visited[start] = true;
    EdgeNode* current = graph->vertices[start].firstEdge;
    while (current != NULL) {
        if (!visited[current->adjVertex]) {
            al_dfsHelper(graph, current->adjVertex, visited);
        }
        current = current->next;
    }
}

void al_dfs(AdjacencyList* graph, int start) {
    bool visited[MAX_VERTEX_NUM];
    int i;
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return;
    }
    if (start < 0 || start >= graph->vertexCount) {
        printf("错误: 无效起始顶点索引 %d\n", start);
        return;
    }
    for (i = 0; i < MAX_VERTEX_NUM; i++) {
        visited[i] = false;
    }
    printf("从 %c 开始的深度优先遍历: ", graph->vertices[start].data);
    al_dfsHelper(graph, start, visited);
    printf("\n");

    for (i = 0; i < graph->vertexCount; i++) {
        if (!visited[i]) {
            printf("从 %c 开始的深度优先遍历 (非连通分量): ", graph->vertices[i].data);
            al_dfsHelper(graph, i, visited);
            printf("\n");
        }
    }
}

void al_bfs(AdjacencyList* graph, int start) {
    bool visited[MAX_VERTEX_NUM];
    int queue[MAX_VERTEX_NUM];
    int front = 0, rear = 0;
    int i;
    if (graph == NULL) {
        printf("错误: 图为空\n");
        return;
    }
    if (start < 0 || start >= graph->vertexCount) {
        printf("错误: 无效起始顶点索引 %d\n", start);
        return;
    }
    for (i = 0; i < MAX_VERTEX_NUM; i++) {
        visited[i] = false;
    }
    printf("从 %c 开始的广度优先遍历: ", graph->vertices[start].data);
    queue[rear++] = start;
    visited[start] = true;
    while (front < rear) {
        int current = queue[front++];
        printf("%c ", graph->vertices[current].data);
        EdgeNode* edge = graph->vertices[current].firstEdge;
        while (edge != NULL) {
            if (!visited[edge->adjVertex]) {
                visited[edge->adjVertex] = true;
                queue[rear++] = edge->adjVertex;
            }
            edge = edge->next;
        }
    }
    printf("\n");

    for (i = 0; i < graph->vertexCount; i++) {
        if (!visited[i]) {
            printf("从 %c 开始的广度优先遍历 (非连通分量): ", graph->vertices[i].data);
            front = rear = 0;
            queue[rear++] = i;
            visited[i] = true;
            while (front < rear) {
                int current = queue[front++];
                printf("%c ", graph->vertices[current].data);
                EdgeNode* edge = graph->vertices[current].firstEdge;
                while (edge != NULL) {
                    if (!visited[edge->adjVertex]) {
                        visited[edge->adjVertex] = true;
                        queue[rear++] = edge->adjVertex;
                    }
                    edge = edge->next;
                }
            }
            printf("\n");
        }
    }
}
