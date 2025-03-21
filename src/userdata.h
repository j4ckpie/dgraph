#ifndef USERDATA_H
#define USERDATA_H

// User input data structure
typedef struct userdata {
    int k;
    double x;
    char *filetype;
    char *input;
} userdata;

userdata* initialize_userdata();

#endif