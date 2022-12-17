#include "graph.h"

namespace Graph {
Solution bfs(const AdjMatrix& edges, Vertex v1, Vertex v2) {
    if (v1 == v2) {
        return {{v1}, 0};
    }

    std::queue<Path> paths;
    paths.push({v1});

    int min_cost = std::numeric_limits<int>::max();
    Path min_path;
    while (!paths.empty()) {
        Path path = paths.front();
        paths.pop();

        Vertex last_v = path.back();

        if (edges.at(last_v).at(v2)) {
            path.push_back(v2);
            int cost = Graph::cost(edges, path);
            if (cost < min_cost) {
                min_cost = cost;
                min_path = path;
            }
        } else if (Graph::cost(edges, path) < min_cost) {
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

    Path path = {v1};
    std::vector<int> idxs = {0};

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

    while (true) {
        int min_cost = std::numeric_limits<int>::max();
        Vertex src_v = -1, dest_v = -1;
        for (auto& pair : paths) {
            Vertex min_v = -1;
            int min_w = std::numeric_limits<int>::max();
            for (int i = 0, n = edges.size(); i < n; i++) {
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
        if (src_v == -1) {
            break;
        }
        paths[dest_v] = {paths.at(src_v).path, min_cost};
        paths.at(dest_v).path.push_back(src_v);
        if (dest_v == v2) {
            Path path = paths.at(dest_v).path;
            path.push_back(dest_v);
            return {path, paths.at(dest_v).cost};
        }
    }

    return {{}, std::numeric_limits<int>::max()};
}
}  // namespace Graph
