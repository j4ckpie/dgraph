#include <stdio.h>

#include <getopt.h>
#include "flags_config.h"

int main(int argc, char **argv) {
    int opt;
    int option_index;

    // Handling input flags
    while((opt = getopt_long(argc, argv, "hkxfi:", long_options, &option_index)) != -1) {
        switch(opt) {
            case 'h':
                // Display help
                break;
            case 'k':
                // Set the amount of subgraphs
                break;
            case 'x':
                // Set max percent margin
                break;
            case 'f':
                // Set filetype
                break;
            case 'i':
                // Set path to input file
                break;
        }
    }

    return 0;
}