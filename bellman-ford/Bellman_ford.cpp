#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sys/time.h>


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


void bellman_ford(int *G, int *dist,bool *negative_cycle, int n ) {
    
    *negative_cycle = false;
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    //initialize
    dist[0] = 0;

    //change in distance
    bool change;
    
    for (int i = 0; i < n - 1; i++) {
        change = false;
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                int weight = G[utils::convert_dimension_2D_1D(u, v, n)];
                if (weight < INF) { //check if an edge exists or not
                    if (dist[u] + weight < dist[v]) {
                        change = true;
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }
    
        if(!change) {
            return;
        }
    }
    //negative cycle detection
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            int weight = G[utils::convert_dimension_2D_1D(u, v, n)];
            if (weight < INF) {
                if (dist[u] + weight < dist[v]) { 
                    *negative_cycle = true;
                    return;
                }
            }
        }
    }
}

int main(int argc, char **argv) {
  
    string filename = argv[1];
    assert(utils::read_file(filename) == 0);

    int *dist;
    bool negative_cycle;

    dist = (int *) malloc(sizeof(int) * utils::N);

   
    bellman_ford( utils::G, dist, &negative_cycle,utils::N);

    return 0;
}