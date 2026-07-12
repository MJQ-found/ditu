#include <stdio.h>
#include "graph_adj_matrix.h"

int main() {
    GraphAdjMatrix graph;
    
    printf("=== 景区路径规划系统 (邻接矩阵实现) ===\n\n");
    
    createGraph(&graph, 0);
    
    addVertex(&graph, "大门");
    addVertex(&graph, "湖中心");
    addVertex(&graph, "山顶");
    addVertex(&graph, "凉亭");
    addVertex(&graph, "花园");
    
    addEdge(&graph, "大门", "湖中心", 200);
    addEdge(&graph, "大门", "花园", 100);
    addEdge(&graph, "湖中心", "山顶", 350);
    addEdge(&graph, "湖中心", "凉亭", 150);
    addEdge(&graph, "凉亭", "山顶", 200);
    addEdge(&graph, "花园", "凉亭", 180);
    
    displayVertexList(&graph);
    
    displayGraph(&graph);
    
    destroyGraph(&graph);
    
    printf("\n程序运行结束!\n");
    return 0;
}