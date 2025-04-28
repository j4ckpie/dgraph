#ifndef GRAPH_H
#define GRAPH_H

#include "userdata.h"

typedef struct {
    int n;
    int m;
    int *row;
    int *col;
} Graph;

Graph* build_graph_from_hyperedges(int n, int *group, int *gptr, int gptrCount);
Graph* read_graph(UserData *data);
void free_graph(Graph *g);
void initial_partition(Graph *g, int *part, int k, int *partSize);
int compute_cut_edges(Graph *g, int *part);
int valid_balance(int *partSize, int avg, double x, int p, int q, int v_move);
int delta_cut(Graph *g, int *part, int v, int current, int q);
int* multi_start_partition(Graph *g, int k, double x, int num_starts);
void simulated_annealing_partition(Graph *g, int *part, int k, double x, int *partSize);
void local_refinement(Graph *g, int *part, int k, double x, int *partSize);
#endif