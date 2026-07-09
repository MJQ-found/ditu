#include <stdio.h>
#include "adjacency_list.h"

void displayMenu() {
    printf("\n");
    printf("=====================================\n");
    printf("        景区路径规划系统              \n");
    printf("=====================================\n");
    printf("  1. 创建景区图                      \n");
    printf("  2. 添加景点                        \n");
    printf("  3. 添加路径                        \n");
    printf("  4. 显示景区图                      \n");
    printf("  5. 显示景点链表                    \n");
    printf("  6. 深度优先遍历                    \n");
    printf("  0. 退出系统                        \n");
    printf("=====================================\n");
    printf("请输入操作选项: ");
}

void showVertexList(AdjacencyList* graph) {
    if (graph == NULL) {
        printf("错误: 景区图为空\n");
        return;
    }
    printf("\n景点链表:\n");
    printf("编号\t景点\t相邻路径数\n");
    printf("-----------------------------\n");
    int i;
    for (i = 0; i < graph->vertexCount; i++) {
        int edgeCount = 0;
        EdgeNode* current = graph->vertices[i].firstEdge;
        while (current != NULL) {
            edgeCount++;
            current = current->next;
        }
        printf("%d\t%c\t%d\n", i, graph->vertices[i].data, edgeCount);
    }
}

void runAutoTest() {
    AdjacencyList* scenicGraph = NULL;
    
    printf("=====================================\n");
    printf("      景区路径规划系统 - 自动测试       \n");
    printf("=====================================\n\n");
    
    printf("【步骤1: 创建景区图】\n");
    scenicGraph = al_create(false);
    if (scenicGraph != NULL) {
        printf("成功创建景区图！\n\n");
    }
    
    printf("【步骤2: 添加景点】\n");
    char spots[] = {'A', 'B', 'C', 'D', 'E'};
    char names[][20] = {"入口广场", "湖心亭", "观景台", "植物园", "游乐场"};
    int i;
    for (i = 0; i < 5; i++) {
        int idx = al_addVertex(scenicGraph, spots[i]);
        printf("成功添加景点 '%c' (%s)，编号为 %d\n", spots[i], names[i], idx);
    }
    printf("\n");
    
    printf("【步骤3: 添加路径】\n");
    int paths[][3] = {{0, 1, 100}, {0, 2, 200}, {1, 3, 150}, {2, 3, 180}, {3, 4, 120}, {1, 4, 250}};
    for (i = 0; i < 6; i++) {
        int from = paths[i][0];
        int to = paths[i][1];
        int weight = paths[i][2];
        al_addEdge(scenicGraph, from, to, weight);
        printf("成功添加路径: %c -> %c，长度 %d 米\n",
               spots[from], spots[to], weight);
    }
    printf("\n");
    
    printf("【步骤4: 显示景区图】\n");
    al_print(scenicGraph);
    printf("\n");
    
    printf("【步骤5: 显示景点链表】\n");
    showVertexList(scenicGraph);
    printf("\n");
    
    printf("【步骤6: 深度优先遍历】\n");
    al_dfs(scenicGraph, 0);
    
    al_destroy(scenicGraph);
    printf("\n感谢使用景区路径规划系统！\n");
}

void runInteractive() {
    AdjacencyList* scenicGraph = NULL;
    int choice;
    char scenicName;
    int from, to, weight;

    printf("欢迎使用景区路径规划系统！\n");

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (scenicGraph != NULL) {
                    al_destroy(scenicGraph);
                    printf("已销毁旧的景区图\n");
                }
                scenicGraph = al_create(false);
                if (scenicGraph != NULL) {
                    printf("成功创建景区图！\n");
                }
                break;

            case 2:
                if (scenicGraph == NULL) {
                    printf("错误: 请先创建景区图\n");
                    break;
                }
                printf("请输入景点名称 (单个字符): ");
                scanf(" %c", &scenicName);
                int idx = al_addVertex(scenicGraph, scenicName);
                if (idx != -1) {
                    printf("成功添加景点 '%c'，编号为 %d\n", scenicName, idx);
                }
                break;

            case 3:
                if (scenicGraph == NULL) {
                    printf("错误: 请先创建景区图\n");
                    break;
                }
                if (scenicGraph->vertexCount < 2) {
                    printf("错误: 至少需要两个景点才能添加路径\n");
                    break;
                }
                printf("请输入路径起点编号: ");
                scanf("%d", &from);
                printf("请输入路径终点编号: ");
                scanf("%d", &to);
                printf("请输入路径长度 (米): ");
                scanf("%d", &weight);
                if (al_addEdge(scenicGraph, from, to, weight) == 0) {
                    printf("成功添加路径: %c -> %c，长度 %d 米\n",
                           al_getVertex(scenicGraph, from),
                           al_getVertex(scenicGraph, to),
                           weight);
                }
                break;

            case 4:
                if (scenicGraph == NULL) {
                    printf("错误: 景区图为空\n");
                    break;
                }
                al_print(scenicGraph);
                break;

            case 5:
                showVertexList(scenicGraph);
                break;

            case 6:
                if (scenicGraph == NULL) {
                    printf("错误: 景区图为空\n");
                    break;
                }
                if (scenicGraph->vertexCount == 0) {
                    printf("错误: 景区图中没有景点\n");
                    break;
                }
                printf("请输入起始景点编号: ");
                scanf("%d", &from);
                al_dfs(scenicGraph, from);
                break;

            case 0:
                if (scenicGraph != NULL) {
                    al_destroy(scenicGraph);
                }
                printf("感谢使用景区路径规划系统！\n");
                return;

            default:
                printf("无效选项，请重新输入\n");
        }
    }
}

int main() {
    runAutoTest();
    return 0;
}
