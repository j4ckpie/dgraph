#include <stdio.h>
#include <string.h>

#include "filetype.h"

// Parse string to enum
FileType parse_filetype(const char *str) {
    if(strcmp(str, "text") == 0 || strcmp(str, "TEXT") == 0) {
        return TEXT;
    } else if(strcmp(str, "binary") == 0 || strcmp(str, "BINARY") == 0) {
        return BINARY;
    } else {
        return UNKNOWN;
    }
}

// Parse enum to string
char* filetype_to_string(FileType filetype) {
    switch(filetype) {
        case TEXT:
            return "text";
        case BINARY:
            return "binary";
        case UNKNOWN:
            return "unknown";
    }
    return "NULL";
}