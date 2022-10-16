#include "path.h"

// Path
struct Path new_path(int n) {
    struct Path p = {.len = 0, .max_len = n, .path = calloc(n, sizeof(int))};
    return p;
}

void del_path(struct Path* p) { free(p->path); }

struct Path copy_path(struct Path* p) {
    struct Path new_p = new_path(p->max_len);
    new_p.len = p->len;
    memcpy(new_p.path, p->path, p->len * sizeof(int));
    return new_p;
}

void append_path(struct Path* p, int v) {
    if (p->len >= p->max_len) {
        p->max_len *= 2;
        int* old = p->path;
        p->path = calloc(p->max_len, sizeof(int));
        memcpy(p->path, old, p->len * sizeof(int));
        free(old);
    }

    p->path[p->len] = v;
    p->len++;
}

struct Path append_path_copy(struct Path* p, int v) {
    struct Path new_p = copy_path(p);
    append_path(&new_p, v);
    return new_p;
}

int first_in_path(struct Path* p) { return p->path[0]; }

int last_in_path(struct Path* p) { return p->path[p->len - 1]; }

void print_path(struct Path* p) {
    printf("[");
    for (int i = 0; i < p->len; i++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%d", p->path[i]);
    }
    printf("]\n");
}

int vertex_in_path(struct Path* p, int v) {
    for (int i = 0; i < p->len; i++) {
        if (p->path[i] == v) {
            return 1;
        }
    }
    return 0;
}

int path_cost(struct Path* p, struct AdjMatrix* am) {
    int cost = 0;
    for (int i = 0; i < p->len - 1; i++) {
        cost += am->edges[p->path[i]][p->path[i + 1]];
    }
    return cost;
}
