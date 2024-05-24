#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int numVertices;
    int numColumns;
    int **adjMatrix;
    int isValid;
} Graph;

#endif // TYPES_H
