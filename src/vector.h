#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    int *data;
    int size;
    int capacity;
} IntVector;

void vector_init(IntVector *vec);
void vector_push_back(IntVector *vec, int value);
void vector_free(IntVector *vec);

#endif