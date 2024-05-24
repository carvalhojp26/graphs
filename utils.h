#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

typedef struct {
    int numVertices;  // Número de vértices no grafo
    int numColumns;   // Número de colunas na matriz de adjacência
    int **adjMatrix;  // Matriz de adjacência
} Graph;

Graph createGraph(int numVertices);
int loadGraphFromFile(Graph *g, const char *filename);
int addVertex(Graph *g);
void printGraph(Graph *g);
void freeGraph(Graph *g);
int removeVertex(Graph *g, int vertex);
int removeEdge(Graph *g, int vertex1, int vertex2);
int addEdge(Graph *g, int vertex1, int vertex2, int weight);
void findPaths(Graph *g, int start, int end);
void dfs(Graph *g, int start, int end, bool *visited, int *path, int pathIndex, int currentSum);
void dfsMaxCost(Graph *g, int start, int end, bool *visited, int *path, int pathIndex, int currentSum, int *maxCost, int *bestPath, int *bestPathLength);
void findMaxCostPath(Graph *g);

#endif // UTILS_H
