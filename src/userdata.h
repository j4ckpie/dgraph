#ifndef USERDATA_H
#define USERDATA_H

#include "filetype.h"

// User input data structure
typedef struct UserData {
    int k;
    double x;
    FileType filetype;
    char *input;
} UserData;

UserData* initialize_userdata();

#endif