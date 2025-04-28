#include "vector.h"
#include <stdlib.h>

void vector_init(IntVector *vec) {
    vec->capacity = 4;
    vec->size = 0;
    vec->data = malloc(vec->capacity * sizeof(int));
}

void vector_push_back(IntVector *vec, int value) {
    if(vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(int));
    }
    vec->data[vec->size++] = value;
}

void vector_free(IntVector *vec) {
    free(vec->data);
}