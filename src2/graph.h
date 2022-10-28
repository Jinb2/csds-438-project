#pragma once

#include <algorithm>
#include <limits>
#include <queue>
#include <stack>
#include <unordered_map>

#include "parse.h"

namespace Graph {
Solution bfs(const AdjMatrix& edges, Vertex v1, Vertex v2);

Solution dfs(const AdjMatrix& edges, Vertex v1, Vertex v2);

Solution dijkstra(const AdjMatrix& edges, Vertex v1, Vertex v2);
}  // namespace Graph
