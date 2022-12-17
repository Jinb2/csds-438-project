#include "graph.h"
#include <omp.h>

namespace Graph {
Solution bfs(const AdjMatrix& edges, Vertex v1, Vertex v2) {
    if (v1 == v2) {
        return {{v1}, 0};
    }
    
    std::vector<Path> paths;

    for (int v = 0; v < edges.size(); v++) {
        if (edges.at(v1).at(v)) {
            paths.push_back({v1, v});
        }
    } 

    const int N = 25;

    if (paths.empty()) {
        return {{}, std::numeric_limits<int>::max()};
    }

    std::vector<Solution> slns(paths.size());
    int min_cost = std::numeric_limits<int>::max();
    int min_depth = 0;
    #pragma omp parallel shared (edges, paths, slns, min_cost, min_depth, v2)
    {
    #pragma omp for
    for (int i = 0; i < N; i++) {
        if (i < paths.size()) {
            slns.at(i) = bfs(edges, paths.at(i), v2, min_cost, min_depth);
            Solution& s = slns.at(i);
            #pragma omp critical
            {
            if (s.cost < min_cost) {
                #pragma omp capture
                {
                min_cost = s.cost;
                min_depth = s.path.size();
                }
            }
            }
        }
    }
    }

    Solution best_sln = slns.at(0);
    for (Solution& sln : slns) {
        if (sln.cost < best_sln.cost) {
            best_sln = sln;
        }
    }

    return best_sln;
}

Solution bfs(const AdjMatrix& edges, Path start, Vertex v2, int& global_min_cost, int& global_min_depth) {
    if (start.back() == v2) {
        return {start, Graph::cost(edges, start)};
    }

    std::queue<Path> paths;
    paths.push(start);

    int min_cost = std::numeric_limits<int>::max();
    Path min_path;
    while (!paths.empty()) {
        Path path = paths.front();
        paths.pop();

        if (min_cost > global_min_cost && path.size() > global_min_depth) {
            break;
        }

        Vertex last_v = path.back();

        if (edges.at(last_v).at(v2)) {
            path.push_back(v2);
            int cost = Graph::cost(edges, path);
            if (cost < min_cost) {
                min_cost = cost;
                min_path = path;
            }
        } else {
            for (int v = 0; v < edges.size(); v++) {
                if (edges.at(last_v).at(v) &&
                    std::find(path.begin(), path.end(), v) == path.end()) {
                    paths.push(path);
                    paths.back().push_back(v);
                }
            }
        }
    }

    return {min_path, min_cost};
}

Solution dfs(const AdjMatrix& edges, Vertex v1, Vertex v2) {
    if (v1 == v2) {
        return {{v1}, 0};
    }

    std::vector<Path> paths;

    for (int v = 0; v < edges.size(); v++) {
        if (edges.at(v1).at(v)) {
            paths.push_back({v1, v});
        }
    } 

    const int N = 25;

    if (paths.empty()) {
        return {{}, std::numeric_limits<int>::max()};
    }

    std::vector<Solution> slns(paths.size());
    #pragma omp parallel shared (edges, paths, slns, v2)
    {
    #pragma omp for
    for (int i = 0; i < N; i++) {
        if (i < paths.size()) {
            Path& path = paths.at(i);
            std::vector<int> idxs(path.size(), edges.size());
            idxs.push_back(0);
            slns.at(i) = dfs(edges, path, idxs, v2);
        }
    }
    }

    Solution best_sln = slns.at(0);
    for (Solution& sln : slns) {
        if (sln.cost < best_sln.cost) {
            best_sln = sln;
        }
    }

    return best_sln;
}

Solution dfs(const AdjMatrix& edges, Path path, std::vector<int> idxs, Vertex v2) {
    if (path.back() == v2) {
        return {path, Graph::cost(edges, path)};
    }

    int min_cost = std::numeric_limits<int>::max();
    Path min_path;

    while (!path.empty()) {
        Vertex last_v = path.back();
        int idx = idxs.back()++;
        int i = 0;
        for (; idx >= 0 && i < edges.size(); i++) {
            if (edges.at(last_v).at(i)) {
                idx--;
            }
        }
        if (idx != -1) {
            path.pop_back();
            idxs.pop_back();
        } else {
            Vertex v = i - 1;
            if (v == v2) {
                path.push_back(v2);
                int cost = Graph::cost(edges, path);
                if (cost < min_cost) {
                    min_cost = cost;
                    min_path = path;
                }
                path.pop_back();
            } else if (std::find(path.begin(), path.end(), v) == path.end()) {
                path.push_back(v);
                idxs.push_back(0);
            }
        }
    }

    return {min_path, min_cost};
}

Solution dijkstra(const AdjMatrix& edges, Vertex v1, Vertex v2) {
    if (v1 == v2) {
        return {{v1}, 0};
    }

    std::unordered_map<Vertex, Solution> paths = {{v1, {{}, 0}}};

    Solution soln = {{}, std::numeric_limits<int>::max()}; 

    std::vector<std::pair<int, std::pair<Vertex, Vertex>>> min_vals;

    #pragma omp parallel shared (edges, paths, v2, min_vals, soln) num_threads(10)
    {
    const int num_threads = omp_get_num_threads();
    const int block_w = (int)(edges.size() / num_threads);

    #pragma omp single
    {
        min_vals.resize(num_threads);
    }

    int id = omp_get_thread_num();
    int start = id * block_w;
    int end = id == num_threads - 1 ? edges.size() : start + block_w;
    while (true) {
        int min_cost = std::numeric_limits<int>::max();
        Vertex src_v = -1, dest_v = -1;
        for (auto& pair : paths) {
            Vertex min_v = -1;
            int min_w = std::numeric_limits<int>::max();
            for (int i = start; i < end; i++) {
                if (i == pair.first) {
                    continue;
                }
                int w = edges.at(pair.first).at(i);
                if (w && w < min_w && paths.find(i) == paths.end()) {
                    min_w = w;
                    min_v = i;
                }
            }
            if (min_v == -1) {
                continue;
            }
            int w = pair.second.cost + min_w;
            if (w < min_cost) {
                min_cost = w;
                src_v = pair.first;
                dest_v = min_v;
            }
        }
        min_vals.at(id) = {min_cost, {src_v, dest_v}};
        #pragma omp barrier
        {}
        #pragma omp single copyprivate(min_cost, src_v, dest_v)
        {
            for (auto pair : min_vals) {
                if (pair.first < min_cost) {
                    min_cost = pair.first;
                    src_v = pair.second.first;
                    dest_v = pair.second.second;
                }
            }
            paths[dest_v] = {paths.at(src_v).path, min_cost};
            paths.at(dest_v).path.push_back(src_v);
            if (dest_v == v2) {
                Path path = paths.at(dest_v).path;
                path.push_back(dest_v);
                soln = {path, paths.at(dest_v).cost};
                src_v = -1;
            }
        }
        if (src_v == -1) {
            break;
        }
    }
    }

    return soln;
}
}  // namespace Graph
