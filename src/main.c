#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

#include "flags.h"
#include "userdata.h"
#include "filetype.h"
#include "io.h"
#include "graph.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    if(argc < 2) {
        fprintf(stderr, "[!] Brak argumentów wejściowych. Przerywam działanie.\n");
        return EXIT_FAILURE;
    }

    int opt;
    int option_index;

    UserData *data = initialize_userdata();

    // Handling input flags
    while((opt = getopt_long(argc, argv, "hkxfi:", long_options, &option_index)) != -1) {
        switch(opt) {
            case 'h':
                // Display help
                print_help();
                return EXIT_SUCCESS;
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
                data->filetype = parse_filetype(optarg);
                break;
            case 'i':
                // Set path to input file
                data->input = optarg;
                break;
        }
    }

    // Test inputted data
    if(test_userdata(data) == 1) {
        return EXIT_FAILURE;
    }

    printf("\n");

    // Summarise and print data
    print_userdata(data);

    Graph *g = read_graph(data->input);
    if(!g) {
        fprintf(stderr, "Nie udało się wczytać grafu.\n");
        return EXIT_FAILURE;
    }
    printf("Wczytano graf: n = %d, m = %d\n", g->n, g->m);

    if (g->n % data->k != 0) {
        double min_x = (100.0 * data->k) / g->n;
        if (data->x < min_x) {
            fprintf(stderr, "Podział nie istnieje - minimalna tolerancja to %.2f%%, a podano %.2f%%\n", min_x, data->x);
            free_graph(g);
            return EXIT_FAILURE;
        }
    }

    multi_start_partition(g, data->k, data->x, 50);
    
    free_graph(g);

    return EXIT_SUCCESS;
}