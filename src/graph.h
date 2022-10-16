#ifndef GRAPH_H
#define GRAPH_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "parse.h"
#include "path.h"
#include "solution.h"

void print_usage();

struct Solution bfs(int v1, int v2, struct AdjMatrix* am);

#endif
