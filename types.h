/**
 * @file types.h
 * @author Joao Paulo Carvalho (27991)
 * @brief
 * @version 0.1
 * @date 2024-05-24
 * @copyright Copyright (c) 2020
 *
 */

#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int numVertices;
    int numColumns;
    int **adjMatrix;
    int isValid;
} Graph;

#endif // TYPES_H
