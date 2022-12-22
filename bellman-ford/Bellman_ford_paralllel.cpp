
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sys/time.h>

#include "omp.h"


#define INF 1000000


namespace utils {
    int N; 
    int *G; 

    
   
    int convert_dimension_2D_1D(int x, int y, int n) {
        return x * n + y;
    }

    int read_file(string filename) {
        std::ifstream inputf(filename, std::ifstream::in);
        if (!inputf.good()) {
            abort_with_error_message("ERROR");
        }
        inputf >> N;
        
        assert(N < (1024 * 1024 * 20));
        G = (int *) malloc(N * N * sizeof(int));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                inputf >> G[convert_dimension_2D_1D(i, j, N)];
            }
        return 0;
    }

}


void bellman_ford(int p, int n, int *G, int *dist, bool *negative_cycle) {

    int local_start[p], local_end[p];
    *negative_cycle = false;

    
    omp_set_num_threads(p);

    
    int ave = n / p;
#pragma omp parallel for
    for (int i = 0; i < p; i++) {
        local_start[i] = ave * i;
        local_end[i] = ave * (i + 1);
        if (i == p - 1) {
            local_end[i] = n;
        }
    }

    
    
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    ////initialize
    dist[0] = 0;

    int iter_num = 0;
    bool change;
    bool local_change[p];
#pragma omp parallel
    {
        int my_rank = omp_get_thread_num();
        for (int iter = 0; iter < n - 1; iter++) {
            local_change[my_rank] = false;
            for (int u = 0; u < n; u++) {
                for (int v = local_start[my_rank]; v < local_end[my_rank]; v++) {
                    int weight = G[utils::convert_dimension_2D_1D(u, v, n)];
                    if (weight < INF) {
                        int new_dis = dist[u] + weight;
                        if (new_dis < dist[v]) {
                            local_change[my_rank] = true;
                            dist[v] = new_dis;
                        }
                    }
                }
            }
#pragma omp barrier
#pragma omp single
            {
                iter_num++;
                change = false;
                for (int rank = 0; rank < p; rank++) {
                    change |= local_change[rank];
                }
            }
            if (!change) {
                break;
            }
        }
    }
    //negative cycle detection
    if (iter_num == n - 1) {
        change = false;
        for (int u = 0; u < n; u++) {
#pragma omp parallel for reduction(|:change)
            for (int v = 0; v < n; v++) {
                int weight = G[u * n + v];
                if (weight < INF) {
                    if (dist[u] + weight < dist[v]) { 
                        change = true;;
                    }
                }
            }
        }
        *negative_cycle = change;
    }

    

int main(int argc, char **argv) {
    
    string filename = argv[1];
    int p = atoi(argv[2]);

    int *dist;
    bool negative_cycle = false;


    assert(utils::read_file(filename) == 0);
    dist = (int *) malloc(sizeof(int) * utils::N);


    bellman_ford(p, utils::N, utils::G, dist, &negative_cycle);


    return 0;
}