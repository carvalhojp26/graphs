/**
 * @file main.c
 * @author Joao Paulo Carvalho (27991)
 * @brief
 * @version 0.1
 * @date 2024-05-25
 * @copyright Copyright (c) 2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "types.h"
#include "logic.h"

int main() {
    const char *filename = "data.txt";
    Graph graph = createGraph(1);  // Cria um grafo com um vértice inicial

    // Carregar grafo
    if (loadGraphFromFile(&graph, filename)) {
        printf("Falha ao carregar o grafo do arquivo.\n");
        freeGraph(&graph);
        return 1;
    }

    printf("Grafo após carregamento do arquivo:\n");
    printGraph(&graph);

    // Adicionar vertice
    if (addVertex(&graph)) {
        printf("Falha ao adicionar novo vértice.\n");
        freeGraph(&graph);
        return 1;
    }

    printf("Grafo após adicionar um novo vértice:\n");
    printGraph(&graph);

    // Remover vertice
    int vertexToRemove = 5;
    if (removeVertex(&graph, vertexToRemove)) {
        printf("Falha ao remover o vértice %d.\n", vertexToRemove);
        freeGraph(&graph);
        return 1;
    }

    printf("Grafo após remover o vértice %d:\n", vertexToRemove);
    printGraph(&graph);

    // Remover aresta
    int vertex1 = 2, vertex2 = 1;
    if (removeEdge(&graph, vertex1, vertex2)) {
        printf("Falha ao remover a aresta de %d para %d.\n", vertex1, vertex2);
    } else {
        printf("Aresta de %d para %d removida com sucesso.\n", vertex1, vertex2);
    }

    printf("Grafo após remover a aresta de %d para %d:\n", vertex1, vertex2);
    printGraph(&graph);

    // Adicionar aresta
    int weight = 10;
    if (addEdge(&graph, vertex1, vertex2, weight)) {
        printf("Falha ao adicionar a aresta de %d para %d.\n", vertex1, vertex2);
    } else {
        printf("Aresta de %d para %d adicionada com sucesso com peso %d.\n", vertex1, vertex2, weight);
    }

    printGraph(&graph);

    // Caminho de X->Y
    printf("Caminhos do vértice %d ao vértice %d\n", vertex1, vertex2);
    findPaths(&graph, vertex1, vertex2);

    // Caminho de maior custo
    findMaxCostPath(&graph);
    freeGraph(&graph);
    return 0;
}
