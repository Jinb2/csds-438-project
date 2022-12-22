#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<std::vector<int>> AdjMatrix;
typedef std::vector<int> Path;
typedef int Vertex;
struct Solution {
    Path path;
    int cost;
};

namespace Graph {
AdjMatrix parse(const std::string& file_name);

int cost(const AdjMatrix& am, const Path& p);
}  // namespace Graph

std::ostream& operator<<(std::ostream& os, const AdjMatrix& am);
std::ostream& operator<<(std::ostream& os, const Path& p);
std::ostream& operator<<(std::ostream& os, const Solution& s);
