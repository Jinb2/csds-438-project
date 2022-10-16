#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// Solution
struct Solution {
    struct Path path;
    int cost;
};

void del_solution(struct Solution* s);

void print_solution(struct Solution* s);
