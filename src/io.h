#ifndef IO_H
#define IO_H

#include "userdata.h"

void print_userdata(UserData *data);
int test_userdata(UserData *data, int n);
void print_help();
int *parse_line_to_ints(char *str, const char *delim, int *count);

#endif