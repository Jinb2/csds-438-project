#include "solution.h"

// Solution
void del_solution(struct Solution* s) { del_path(&s->path); }

void print_solution(struct Solution* s) {
    printf("%d->%d: Cost = %d, ", first_in_path(&s->path),
           last_in_path(&s->path), s->cost);
    print_path(&s->path);
}
