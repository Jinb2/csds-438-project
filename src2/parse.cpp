#include "parse.h"

namespace Graph {
AdjMatrix parse(const std::string& file_name) {
    std::ifstream file("uw_10.gr");
    std::string line;
    // Skip to line 2
    int i = 0;
    for (; i < 2; i++) {
        std::getline(file, line);
    }
    int n = std::stoi(line.substr(line.find(":") + 1));
    AdjMatrix edges(n);
    for (int j = 0; j < n; j++) {
        edges.at(j) = std::vector<int>(n);
    }
    // Skip to line 8
    for (; i < 8; i++) {
        std::getline(file, line);
    }
    char ch;
    int v1, v2, w;
    // Read edges
    while (file >> ch >> v1 >> v2 >> w) {
        edges.at(v1 - 1).at(v2 - 1) = w;
    }
    file.close();

    return edges;
}

int cost(const AdjMatrix& am, const Path& p) {
    int cost = 0;
    for (int i = 0, n = p.size(); i < n - 1; i++) {
        cost += am.at(p.at(i)).at(p.at(i + 1));
    }
    return cost;
}
}  // namespace Graph

std::ostream& operator<<(std::ostream& os, const AdjMatrix& am) {
    for (auto& row : am) {
        bool first = true;
        for (auto w : row) {
            if (!first) {
                os << ", ";
            }
            os << w;
            first = false;
        }
        os << "\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Path& p) {
    bool first = true;
    for (auto v : p) {
        if (!first) {
            os << "->";
        }
        os << v;
        first = false;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Solution& s) {
    os << "Path: " << s.path << ", Cost: " << s.cost;
    return os;
}