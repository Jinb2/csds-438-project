#ifndef PATH_H
#define PATH_H

#include <stdio.h>
#include <string.h>

#include "parse.h"

// Path
struct Path {
    int* path;
    int len, max_len;
};

struct Path new_path(int n);

void del_path(struct Path* p);

struct Path copy_path(struct Path* p);

void append_path(struct Path* p, int v);

struct Path append_path_copy(struct Path* p, int v);

int first_in_path(struct Path* p);

int last_in_path(struct Path* p);

void print_path(struct Path* p);

int vertex_in_path(struct Path* p, int v);

int path_cost(struct Path* p, struct AdjMatrix* am);

#endif
