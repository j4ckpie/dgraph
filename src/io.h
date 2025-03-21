#ifndef IO_H
#define IO_H

#include "userdata.h"

void print_userdata(userdata *data);
int test_userdata(userdata *data);
void print_help();
int *parse_line_to_ints(char *str, const char *delim, int *count);

#endif