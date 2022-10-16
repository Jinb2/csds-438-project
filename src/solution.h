#ifndef SOLUTION_H
#define SOLUTION_H

#include <stdio.h>

#include "path.h"

// Solution
struct Solution {
    struct Path path;
    int cost;
};

void del_solution(struct Solution* s);

void print_solution(struct Solution* s);

#endif
