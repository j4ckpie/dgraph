#include <stdio.h>
#include <stdlib.h>

#include "userdata.h"

// Initalize the structure
userdata* initialize_userdata() {
    userdata *data = malloc(sizeof(userdata));

    // Check if malloc was successful
    if(data == NULL) {
        fprintf(stderr, "Błąd alokacji pamięci na dane wejściowe! Kończę działanie\n");
        return NULL;
    }

    // Allocate memory for filetype and filepath and check if they were successful
    data->filetype = malloc(6 * sizeof(char));
    if(data->filetype == NULL) {
        fprintf(stderr, "Błąd alokacji pamięci na dane wejściowe! Kończę działanie\n");
        return NULL;
    }

    data->filepath = malloc(128 * sizeof(char));
    if(data->filepath == NULL) {
        fprintf(stderr, "Błąd alokacji pamięci na dane wejściowe! Kończę działanie\n");
        return NULL;
    }

    // Set default values
    data->k = 2;
    data->x = 10;
    data->filetype = "text";
    data->filepath = "Undefined";

    return data;
}