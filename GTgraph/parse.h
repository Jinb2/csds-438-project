#include <stdio.h>
#include <stdlib.h>

// AdjMatrix
struct AdjMatrix {
    int** edges;
    int n;
};

struct AdjMatrix new_adj_matrix(int n);

void del_adj_matrix(struct AdjMatrix* am);

void print_adj_matrix(struct AdjMatrix* am);

struct AdjMatrix parse_adj_matrix(const char* graph_file);
