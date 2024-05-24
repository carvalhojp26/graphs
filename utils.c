#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

Graph createGraph(int numVertices) {
    Graph g;
    g.numVertices = numVertices;
    g.numColumns = numVertices;  // Inicialmente, assume-se uma matriz quadrada
    g.adjMatrix = malloc(numVertices * sizeof(int*));
    if (g.adjMatrix == NULL) {
        g.isValid = 0;
        return g;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numVertices; i++) {
        g.adjMatrix[i] = calloc(numVertices, sizeof(int)); // Usa calloc para inicializar com zero
        if (g.adjMatrix[i] == NULL) {
            g.isValid = 0;
            return g;
            exit(EXIT_FAILURE);
        }
    }
    return g;
}

int loadGraphFromFile(Graph *g, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {;
        return 1;
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
    return 0;
}

int addVertex(Graph *g) {
    // Aumenta o número de vértices
    g->numVertices++;

    // Realoca a matriz de adjacência para acomodar o novo vértice
    g->adjMatrix = realloc(g->adjMatrix, g->numVertices * sizeof(int*));
    if (g->adjMatrix == NULL) {
        return 1; // Falha na realocação
    }

    // Aloca e inicializa a nova linha com zeros
    g->adjMatrix[g->numVertices - 1] = calloc(g->numColumns, sizeof(int));
    if (g->adjMatrix[g->numVertices - 1] == NULL) {
        return 1; // Falha na alocação
    }

    // Realoca a matriz de adjacência para todas as colunas existentes
    for (int i = 0; i < g->numVertices - 1; i++) {
        g->adjMatrix[i] = realloc(g->adjMatrix[i], g->numVertices * sizeof(int));
        g->adjMatrix[i][g->numVertices - 1] = 0; // Inicializa a nova coluna com zero
    }

    return 0; // Sucesso
}

int printGraph(Graph *g) {
    printf("Matriz de Adjacência (%d vértices):\n", g->numVertices);
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numColumns; j++) {
            printf("%4d", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

int freeGraph(Graph *g) {
    for (int i = 0; i < g->numVertices; i++) {
        free(g->adjMatrix[i]); // Libera cada linha da matriz
    }
    free(g->adjMatrix); // Libera o array de ponteiros
    g->adjMatrix = NULL;
    g->numVertices = 0;
    g->numColumns = 0;

    return 0;
}

int removeVertex(Graph *g, int vertex) {
    if (vertex < 0 || vertex >= g->numVertices) {
        return 1;  // Falha, índice do vértice fora do intervalo permitido
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
        return 1;
    }

    // Decrementa o número de vértices
    g->numVertices--;

    return 1;  // Sucesso
}

int removeEdge(Graph *g, int vertex1, int vertex2) {
    if (vertex1 < 0 || vertex1 >= g->numVertices || vertex2 < 0 || vertex2 >= g->numVertices) {
        return 1;  // Falha, índice do vértice fora do intervalo permitido
    }

    g->adjMatrix[vertex1][vertex2] = 0;
    return 0;  // Sucesso
}

int addEdge(Graph *g, int vertex1, int vertex2, int weight) {
    if (vertex1 < 0 || vertex1 >= g->numVertices || vertex2 < 0 || vertex2 >= g->numVertices) {
        return 1;  // Falha, índice do vértice fora do intervalo permitido
    }

    g->adjMatrix[vertex1][vertex2] = weight;
    return 0;  // Sucesso
}