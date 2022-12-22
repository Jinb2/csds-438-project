#include <chrono>
#include <random>

#include "graph.h"
#include "parse.h"

int main(int argc, char* argv[]) {
    AdjMatrix am = Graph::parse(argv[1]);
    
	std::vector<int> v1s = {4, 0, 8, 4, 7}, v2s = {9, 5, 1, 3, 5};
    for (int i = 0; i < v1s.size(); i++) {
        auto start = std::chrono::high_resolution_clock::now();
        Solution s = Graph::dijkstra(am, v1s.at(i), v2s.at(i));
        auto stop = std::chrono::high_resolution_clock::now();
        std::cerr << "Dijkstra:\n" << s << std::endl;
        std::cerr << "Time Elapsed: "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(stop -
                                                                          start)
                         .count()
                  << std::endl;
    }

    return 0;
}
