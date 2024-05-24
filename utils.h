#ifndef UTILS_H
#define UTILS_H

#include "types.h"

Graph createGraph(int numVertices);
int loadGraphFromFile(Graph *g, const char *filename);
int addVertex(Graph *g);
int printGraph(Graph *g);
int freeGraph(Graph *g);
int removeVertex(Graph *g, int vertex);
int removeEdge(Graph *g, int vertex1, int vertex2);
int addEdge(Graph *g, int vertex1, int vertex2, int weight);

#endif // UTILS_H
