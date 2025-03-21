#ifndef USERDATA_H
#define USERDATA_H

#include "filetype.h"

// User input data structure
typedef struct UserData {
    int k;
    int x;
    FileType filetype;
    char *input;
} UserData;

UserData* initialize_userdata();
char* filetype_to_string();

#endif