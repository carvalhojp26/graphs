// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main() {
    const char *filename = "data.txt";  // Nome do arquivo contendo a matriz de adjacência

    // Assume que o arquivo existe e contém pelo menos uma linha.
    Graph graph = createGraph(1);  // Inicia com 1 para evitar problemas com malloc/calloc de zero itens.

    // Carrega o grafo do arquivo
    if (!loadGraphFromFile(&graph, filename)) {
        printf("Falha ao carregar o grafo do arquivo.\n");
        freeGraph(&graph);
        return 1;  // Encerra a execução com erro
    }

    // Imprime o grafo após o carregamento
    printf("Grafo após carregamento do arquivo:\n");
    printGraph(&graph);

    // Adiciona um novo vértice ao grafo
    if (!addVertex(&graph)) {
        printf("Falha ao adicionar novo vértice.\n");
        freeGraph(&graph);
        return 1;  // Encerra a execução com erro
    }

    // Imprime o grafo após a adição do novo vértice
    printf("Grafo após adicionar um novo vértice:\n");
    printGraph(&graph);

    int vertexToRemove = 5;  // Pode ajustar conforme a necessidade ou entrada do usuário
    if (!removeVertex(&graph, vertexToRemove)) {
        printf("Falha ao remover o vértice %d.\n", vertexToRemove);
        freeGraph(&graph);
        return 1;
    }

    // Imprime o grafo após a remoção do vértice
    printf("Grafo após remover o vértice %d:\n", vertexToRemove);
    printGraph(&graph);

    int vertex1 = 2;
    int vertex2 = 1;

    printf("Tentando remover a aresta de %d para %d.\n", vertex1, vertex2);
    if (!removeEdge(&graph, vertex1, vertex2)) {
        printf("Falha ao remover a aresta de %d para %d.\n", vertex1, vertex2);
    } else {
        printf("Aresta de %d para %d removida com sucesso.\n", vertex1, vertex2);
    }

    // Imprime o grafo após a remoção da aresta
    printf("Grafo após remover a aresta de %d para %d:\n", vertex1, vertex2);
    printGraph(&graph);

    // Libera os recursos alocados para o grafo

    printGraph(&graph);

    int weight = 10;

    printf("Tentando adicionar a aresta de %d para %d com peso %d.\n", vertex1, vertex2, weight);
    if (!addEdge(&graph, vertex1, vertex2, weight)) {
        printf("Falha ao adicionar a aresta de %d para %d.\n", vertex1, vertex2);
    } else {
        printf("Aresta de %d para %d adicionada com sucesso com peso %d.\n", vertex1, vertex2, weight);
    }

    printGraph(&graph);

    printf("Caminhos do vértice 0 ao vértice 4:\n");
    findPaths(&graph, 0, 4);

    freeGraph(&graph);
    return 0;  // Finaliza a execução com sucesso
}