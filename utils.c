#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph createGraph(int numVertices) {
    Graph g;
    g.numVertices = numVertices;
    g.numColumns = numVertices;  // Inicialmente, assume-se uma matriz quadrada
    g.adjMatrix = malloc(numVertices * sizeof(int*));
    if (g.adjMatrix == NULL) {
        printf("Failed to allocate memory for adjacency matrix.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numVertices; i++) {
        g.adjMatrix[i] = calloc(numVertices, sizeof(int)); // Usa calloc para inicializar com zero
        if (g.adjMatrix[i] == NULL) {
            printf("Failed to allocate memory for adjacency matrix row.\n");
            exit(EXIT_FAILURE);
        }
    }
    return g;
}

int loadGraphFromFile(Graph *g, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open the file.\n");
        return 0;
    }

    char line[1024];
    int maxColumns = 0, lineCount = 0;

    // Lê uma vez para determinar o número de linhas e colunas
    while (fgets(line, sizeof(line), file)) {
        int columnCount = 0;
        for (char *token = strtok(line, ";"); token != NULL; token = strtok(NULL, ";")) {
            columnCount++;
        }
        if (columnCount > maxColumns) {
            maxColumns = columnCount;
        }
        lineCount++;
    }

    // Configura o grafo com os tamanhos corretos
    *g = createGraph(lineCount);

    // Reiniciar a leitura do arquivo para carregar a matriz de adjacência
    rewind(file);
    int row = 0;
    while (fgets(line, sizeof(line), file)) {
        int col = 0;
        for (char *token = strtok(line, ";"); token != NULL; token = strtok(NULL, ";")) {
            g->adjMatrix[row][col++] = atoi(token);
        }
        row++;
    }

    fclose(file);
    return 1;
}

int addVertex(Graph *g) {
    // Aumenta o número de vértices
    g->numVertices++;

    // Realoca a matriz de adjacência para acomodar o novo vértice
    g->adjMatrix = realloc(g->adjMatrix, g->numVertices * sizeof(int*));
    if (g->adjMatrix == NULL) {
        printf("Failed to reallocate memory for the adjacency matrix.\n");
        return 0; // Falha na realocação
    }

    // Aloca e inicializa a nova linha com zeros
    g->adjMatrix[g->numVertices - 1] = calloc(g->numColumns, sizeof(int));
    if (g->adjMatrix[g->numVertices - 1] == NULL) {
        printf("Failed to allocate memory for the new vertex.\n");
        return 0; // Falha na alocação
    }

    // Realoca a matriz de adjacência para todas as colunas existentes
    for (int i = 0; i < g->numVertices - 1; i++) {
        g->adjMatrix[i] = realloc(g->adjMatrix[i], g->numVertices * sizeof(int));
        g->adjMatrix[i][g->numVertices - 1] = 0; // Inicializa a nova coluna com zero
    }

    return 1; // Sucesso
}

void printGraph(Graph *g) {
    printf("Matriz de Adjacência (%d vértices):\n", g->numVertices);
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numColumns; j++) {
            printf("%4d", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void freeGraph(Graph *g) {
    for (int i = 0; i < g->numVertices; i++) {
        free(g->adjMatrix[i]); // Libera cada linha da matriz
    }
    free(g->adjMatrix); // Libera o array de ponteiros
    g->adjMatrix = NULL;
    g->numVertices = 0;
    g->numColumns = 0;
}

int removeVertex(Graph *g, int vertex) {
    if (vertex < 0 || vertex >= g->numVertices) {
        printf("Vertex index out of range.\n");
        return 0;  // Falha, índice do vértice fora do intervalo permitido
    }

    // Libera a memória da linha correspondente ao vértice
    free(g->adjMatrix[vertex]);

    // Desloca todas as linhas seguintes para cima para preencher o espaço vazio
    for (int i = vertex; i < g->numVertices - 1; i++) {
        g->adjMatrix[i] = g->adjMatrix[i + 1];
    }

    // Realoca a matriz de adjacência para refletir a remoção de um vértice
    g->adjMatrix = realloc(g->adjMatrix, (g->numVertices - 1) * sizeof(int*));
    if (!g->adjMatrix) {
        printf("Reallocation failed.\n");
        return 0;
    }

    // Decrementa o número de vértices
    g->numVertices--;

    return 1;  // Sucesso
}

int removeEdge(Graph *g, int vertex1, int vertex2) {
    if (vertex1 < 0 || vertex1 >= g->numVertices || vertex2 < 0 || vertex2 >= g->numVertices) {
        printf("Vertex index out of range.\n");
        return 0;  // Falha, índice do vértice fora do intervalo permitido
    }

    g->adjMatrix[vertex1][vertex2] = 0;
    return 1;  // Sucesso
}

int addEdge(Graph *g, int vertex1, int vertex2, int weight) {
    if (vertex1 < 0 || vertex1 >= g->numVertices || vertex2 < 0 || vertex2 >= g->numVertices) {
        printf("Vertex index out of range.\n");
        return 0;  // Falha, índice do vértice fora do intervalo permitido
    }

    g->adjMatrix[vertex1][vertex2] = weight;
    return 1;  // Sucesso
}

void dfs(Graph *g, int start, int end, bool *visited, int *path, int pathIndex, int currentSum) {
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
}

void findPaths(Graph *g, int start, int end) {
    bool *visited = malloc(g->numVertices * sizeof(bool));
    int *path = malloc(g->numVertices * sizeof(int));
    for (int i = 0; i < g->numVertices; i++) {
        visited[i] = false;
    }
    dfs(g, start, end, visited, path, 0, 0);
    free(visited);
    free(path);
}

void findMaxCostPath(Graph *g) {
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
}

void dfsMaxCost(Graph *g, int start, int end, bool *visited, int *path, int pathIndex, int currentSum, int *maxCost, int *bestPath, int *bestPathLength) {
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
}