#include "graph.h"
#include "vector.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

Graph* build_graph_from_hyperedges(int n, int *group, int *gptr, int gptrCount) {
    IntVector *adjList = malloc(n * sizeof(IntVector));
    for (int i = 0; i < n; i++) vector_init(&adjList[i]);
    int numGroups = gptrCount - 1;
    for (int i = 0; i < numGroups; i++) {
        int start = gptr[i];
        int end = gptr[i+1];
        for (int j = start; j < end; j++) {
            for (int k = j+1; k < end; k++) {
                int u = group[j];
                int v = group[k];
                vector_push_back(&adjList[u], v);
                vector_push_back(&adjList[v], u);
            }
        }
    }
    int totalEdges = 0;
    for (int i = 0; i < n; i++) {
        totalEdges += adjList[i].size;
    }
    
    Graph *g = malloc(sizeof(Graph));
    g->n = n;
    g->m = totalEdges / 2;
    g->row = malloc((n+1) * sizeof(int));
    g->col = malloc(totalEdges * sizeof(int));
    
    g->row[0] = 0;
    for (int i = 0; i < n; i++) {
        g->row[i+1] = g->row[i] + adjList[i].size;
        memcpy(&g->col[g->row[i]], adjList[i].data, adjList[i].size * sizeof(int));
    }
    
    for (int i = 0; i < n; i++) {
        vector_free(&adjList[i]);
    }
    free(adjList);
    
    return g;
}

Graph* read_graph(UserData *data) {
    FILE *fp = fopen(data->input, "r");
    if(!fp) {
        perror("Nie można otworzyć pliku");
        exit(EXIT_FAILURE);
    }

    // Open new file to copy to
    char out_file[512];
    char out_path[512];
    char *filetype = "w";
    char *ext = strrchr(data->input, '.');
    if(ext) {
        int len = ext - data->input;
        strncpy(out_file, data->input, len);
        out_file[len] = '\0';

        if(data->filetype == TEXT) {
            strcat(out_file, ".txt");
            filetype = "w";
        }
        else {
            strcat(out_file, ".bin");
            filetype = "wb";
        }

        if (strncmp(out_file, "data/", 5) == 0) {
            sprintf(out_path, "out/%s", out_file + 5);
        }
    }
    FILE *out = fopen(out_path, filetype);
    if(!out) {
        perror("Nie można otworzyć pliku");
        exit(EXIT_FAILURE);
    }

    // Read graph

    char buffer[1<<20];
    
    if(!fgets(buffer, sizeof(buffer), fp)) {
        fprintf(stderr, "Błąd odczytu linii 1.\n");
        exit(EXIT_FAILURE);
    }
    fputs(buffer, out);
    
    if(!fgets(buffer, sizeof(buffer), fp)) {
        fprintf(stderr, "Błąd odczytu linii 2.\n");
        exit(EXIT_FAILURE);
    }
    fputs(buffer, out);
    
    buffer[strcspn(buffer, "\n")] = 0;
    int vertexCount;
    int *vertexTokens = parse_line_to_ints(buffer, ";\n", &vertexCount);
    int n = vertexCount;
    free(vertexTokens);
    
    if(!fgets(buffer, sizeof(buffer), fp)) {
        fprintf(stderr, "Błąd odczytu linii 3.\n");
        exit(EXIT_FAILURE);
    }
    fputs(buffer, out);
    
    if(!fgets(buffer, sizeof(buffer), fp)) {
        fprintf(stderr, "Błąd odczytu linii 4.\n");
        exit(EXIT_FAILURE);
    }
    fputs(buffer, out);

    buffer[strcspn(buffer, "\n")] = 0;
    int groupCount;
    int *group = parse_line_to_ints(buffer, ";\n", &groupCount);

    if(!fgets(buffer, sizeof(buffer), fp)) {
        fprintf(stderr, "Błąd odczytu linii 5.\n");
        exit(EXIT_FAILURE);
    }
    fputs(buffer, out);

    buffer[strcspn(buffer, "\n")] = 0;
    int gptrCount;
    int *gptr = parse_line_to_ints(buffer, ";\n", &gptrCount);
    
    fclose(fp);
    fclose(out);
    
    Graph *g = build_graph_from_hyperedges(n, group, gptr, gptrCount);
    
    free(group);
    free(gptr);
    
    return g;
}

void free_graph(Graph *g) {
    if(g) {
        free(g->row);
        free(g->col);
        free(g);
    }
}


// ??? consider random assigments
// ??? random shuffle
// ??? neighbour of color X, probability of color X >>>> than others
void initial_partition(Graph *g, int *part, int k, int *partSize) {
    for (int i = 0; i < k; i++)
        partSize[i] = 0;
    
    int *order=malloc(g->n*sizeof(int));
    for (int i = 0 ; i < g->n; i++) order[i] = i;
    for (int i=g->n-1; i>0; i--){
        int j=rand()%(i+1);
        int t=order[i]; order[i]=order[j]; order[j]=t;
    }
    for (int i = 0; i < g->n; i++) {
        int v = order[i];
        int p = i % k;
        part[v] = p;
        partSize[p]++;
    }
}

int compute_cut_edges(Graph *g, int *part) {
    int cut = 0;
    for (int v = 0; v < g->n; v++) {
        for (int i = g->row[v]; i < g->row[v+1]; i++) {
            int u = g->col[i];
            if (part[v] != part[u] && u > v)
                cut++;
        }
    }
    return cut;
}

int valid_balance(int *partSize, int avg, double x, int p, int q, int v_move) {
    double lower_bound = avg * (1.0 - x/100.0);
    double upper_bound = avg * (1.0 + x/100.0);
    int newSizeP = partSize[p] - v_move;
    int newSizeQ = partSize[q] + v_move;
    return (newSizeP >= lower_bound && newSizeQ <= upper_bound);
}

int delta_cut(Graph *g, int *part, int v, int current, int q) {
    int delta = 0;
    for (int i = g->row[v]; i < g->row[v+1]; i++) {
        int u = g->col[i];
        if (part[u] == current)
            delta++;
        if (part[u] == q)
            delta--;
    }
    return delta;
}

// messing up with cooling rate and temperature could significantly improve the results
void simulated_annealing_partition(Graph *g, int *part, int k, double x, int *partSize) {
    double T = 50000.0;
    double cooling_rate = 0.999;
    int n = g->n;
    int avg = n / k;
    
    while (T > 1e-4) {
        int v = rand() % n;
        int current = part[v];
        int q = rand() % k;
        if(q == current)
            continue;
        T *= cooling_rate;
        if(partSize[current] == 1) continue;
        if(!valid_balance(partSize, avg, x, current, q, 1)){
            continue;
        }
        int d = delta_cut(g, part, v, current, q);
        if (d < 0 || exp(-d / T) > ((double) rand() / RAND_MAX)) {
            part[v] = q;
            partSize[current]--;
            partSize[q]++;
        }
    }
}

void local_refinement(Graph *g, int *part, int k, double x, int *partSize) {
    int improved = 1;
    int n = g->n;
    int avg = n / k;
    while(improved) {
        improved = 0;
        for (int v = 0; v < n; v++) {
            int current = part[v];
            for (int q = 0; q < k; q++) {
                if (q == current)
                    continue;
                if (!valid_balance(partSize, avg, x, current, q, 1))
                    continue;
                int d = delta_cut(g, part, v, current, q);
                if (d < 0) {
                    if(partSize[current] == 1) continue;
                    part[v] = q;
                    partSize[current]--;
                    partSize[q]++;
                    improved = 1;
                    break;
                }
            }
        }
    }
}
int* multi_start_partition(Graph *g, int k, double x, int num_starts) {
    int n = g->n;
    int best_cut = 1e9;
    int *best_partition = malloc(n * sizeof(int));
    int *current_part = malloc(n * sizeof(int));
    int *current_partSize = malloc(k * sizeof(int));
    for (int start = 0; start < num_starts; start++) {
        initial_partition(g, current_part, k, current_partSize);
        if(rand() % 3 == 0) local_refinement(g, current_part, k, x, current_partSize);
        simulated_annealing_partition(g, current_part, k, x, current_partSize);
        local_refinement(g, current_part, k, x, current_partSize);
        int cut = compute_cut_edges(g, current_part);
        if (cut < best_cut) {
            best_cut = cut;
            memcpy(best_partition, current_part, n * sizeof(int));
        }
    }
    printf("Najlepszy podział: %d krawędzi przecinanych\n", best_cut);
    
    free(current_part);
    free(current_partSize);
    return best_partition;
}