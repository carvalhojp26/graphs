/**
 * @file logic.c
 * @author Joao Paulo Carvalho (27991)
 * @brief
 * @version 0.1
 * @date 2024-05-24
 * @copyright Copyright (c) 2020
 *
 */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"
#include "types.h"

int dfs(Graph *g, int start, int end, bool *visited, int *path, int pathIndex, int currentSum) {
    visited[start] = true;
    path[pathIndex] = start;
    pathIndex++;

    if (start == end) {
        printf("Caminho: ");
        for (int i = 0; i < pathIndex; i++) {
            printf("%d ", path[i]);
        }
        printf(" | Custo: %d\n", currentSum);
    } else {
        for (int i = 0; i < g->numVertices; i++) {
            if (g->adjMatrix[start][i] != 0 && !visited[i]) {
                dfs(g, i, end, visited, path, pathIndex, currentSum + g->adjMatrix[start][i]);
            }
        }
    }

    pathIndex--;
    visited[start] = false;

    return 0;
}

int findPaths(Graph *g, int start, int end) {
    bool *visited = malloc(g->numVertices * sizeof(bool));
    int *path = malloc(g->numVertices * sizeof(int));
    for (int i = 0; i < g->numVertices; i++) {
        visited[i] = false;
    }
    dfs(g, start, end, visited, path, 0, 0);
    free(visited);
    free(path);

    return 0;
}

int findMaxCostPath(Graph *g) {
    int maxCost = 0;
    int *bestPath = malloc(g->numVertices * sizeof(int));
    int bestPathLength = 0;

    for (int start = 0; start < g->numVertices; start++) {
        for (int end = 0; end < g->numVertices; end++) {
            if (start != end) {
                bool *visited = malloc(g->numVertices * sizeof(bool));
                int *path = malloc(g->numVertices * sizeof(int));
                for (int i = 0; i < g->numVertices; i++) {
                    visited[i] = false;
                }
                dfsMaxCost(g, start, end, visited, path, 0, 0, &maxCost, bestPath, &bestPathLength);
                free(visited);
                free(path);
            }
        }
    }

    printf("Caminho de maior custo: ");
    for (int i = 0; i < bestPathLength; i++) {
        printf("%d ", bestPath[i]);
    }
    printf(" | Custo: %d\n", maxCost);

    free(bestPath);

    return 0;
}

int dfsMaxCost(Graph *g, int start, int end, bool *visited, int *path, int pathIndex, int currentSum, int *maxCost, int *bestPath, int *bestPathLength) {
    visited[start] = true;
    path[pathIndex] = start;
    pathIndex++;

    if (start == end) {
        if (currentSum > *maxCost) {
            *maxCost = currentSum;
            *bestPathLength = pathIndex;
            memcpy(bestPath, path, pathIndex * sizeof(int));
        }
    } else {
        for (int i = 0; i < g->numVertices; i++) {
            if (g->adjMatrix[start][i] != 0 && !visited[i]) {
                dfsMaxCost(g, i, end, visited, path, pathIndex, currentSum + g->adjMatrix[start][i], maxCost, bestPath, bestPathLength);
            }
        }
    }

    pathIndex--;
    visited[start] = false;

    return 0;
}