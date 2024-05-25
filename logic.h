/**
 * @file logic.h
 * @author Joao Paulo Carvalho (27991)
 * @brief
 * @version 0.1
 * @date 2024-05-24
 * @copyright Copyright (c) 2020
 *
 */

#ifndef LOGIC_H
#define LOGIC_H

#include "types.h"
#include <stdbool.h>

int dfs(Graph *g, int start, int end, bool *visited, int *path, int pathIndex, int currentSum);
int findPaths(Graph *g, int start, int end);
int findMaxCostPath(Graph *g);
int dfsMaxCost(Graph *g, int start, int end, bool *visited, int *path, int pathIndex, int currentSum, int *maxCost, int *bestPath, int *bestPathLength);

#endif // LOGIC_H
