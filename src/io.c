#include <stdio.h>

#include "userdata.h"

// Print data from user input
void print_userdata(userdata *data) {
    printf("--parts k: %d\n--percent x: %d%%\n--filetype: %s\n--filepath: %s\n",
        data->k, data->x, data->filetype, data->filepath);
}