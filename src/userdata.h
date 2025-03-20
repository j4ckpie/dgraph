#ifndef USERDATA_H
#define USERDATA_H

// User input data structure
typedef struct userdata {
    int k;
    int x;
    char *filetype;
    char *filepath;
} userdata;

userdata* initialize_userdata();

#endif