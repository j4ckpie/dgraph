#ifndef FILETYPE_H
#define FILETYPE_H

// Enumerator for available filetypes
typedef enum {
    TEXT,
    BINARY,
    UNKNOWN
} FileType;

FileType parse_filetype(const char *str);

#endif