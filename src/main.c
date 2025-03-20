#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>
#include "flags.h"

#include "userdata.h"
#include "io.h"

int main(int argc, char **argv) {
    int opt;
    int option_index;

    userdata *data = initialize_userdata();

    // Handling input flags
    while((opt = getopt_long(argc, argv, "hkxfi:", long_options, &option_index)) != -1) {
        switch(opt) {
            case 'h':
                // Display help
                break;
            case 'k':
                // Set the amount of subgraphs
                data->k = atoi(optarg);
                break;
            case 'x':
                // Set max percent margin
                data->x = atoi(optarg);
                break;
            case 'f':
                // Set filetype
                data->filetype = optarg;
                break;
            case 'i':
                // Set path to input file
                data->filepath = optarg;
                break;
        }
    }

    print_userdata(data);

    return 0;
}