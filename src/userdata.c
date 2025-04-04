#include <stdio.h>
#include <stdlib.h>

#include "userdata.h"

// Initalize the structure
UserData* initialize_userdata() {
    UserData *data = malloc(sizeof(UserData));

    // Check if malloc was successful
    if(data == NULL) {
        fprintf(stderr, "[!] Błąd alokacji pamięci na dane wejściowe! Kończę działanie\n");
        return NULL;
    }

    // Allocate memory for filetype and filepath and check if they were successful
    data->input = malloc(128 * sizeof(char));
    if(data->input == NULL) {
        fprintf(stderr, "[!] Błąd alokacji pamięci na dane wejściowe! Kończę działanie\n");
        return NULL;
    }

    // Set default values
    data->k = 2;
    data->x = 10.0;
    data->filetype = TEXT;
    data->input = "Undefined";

    return data;
}