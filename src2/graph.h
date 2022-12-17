#pragma once

#include <algorithm>
#include <limits>
#include <queue>
#include <stack>
#include <unordered_map>

#include "parse.h"

namespace Graph {
Solution bfs(const AdjMatrix& edges, Vertex v1, Vertex v2);
Solution bfs(const AdjMatrix& edges, Path start, Vertex v2, int& global_min_cost, int& global_min_depth);

Solution dfs(const AdjMatrix& edges, Vertex v1, Vertex v2);
Solution dfs(const AdjMatrix& edges, Path path, std::vector<int> idxs, Vertex v2);

Solution dijkstra(const AdjMatrix& edges, Vertex v1, Vertex v2);
}  // namespace Graph
