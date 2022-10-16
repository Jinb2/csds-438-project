#include "graph.h"

// Main
void print_usage() { printf("Usage: graph file.gr\n"); }

struct Solution bfs(int v1, int v2, struct AdjMatrix* am) {
    struct Solution solution = {.path = new_path(1), .cost = 0};
    append_path(&solution.path, v1);

    if (v1 == v2) {
        return solution;
    }

    solution.cost = (int)INFINITY;

    int queue_idx = 0, queue_len = 1, queue_max_len = 10;
    struct Path* queue = malloc(queue_max_len * sizeof(struct Path));
    queue[0] = copy_path(&solution.path);

    while (queue_len > 0) {
        struct Path path = queue[queue_idx];
        queue_idx = (queue_idx + 1) % queue_max_len;
        queue_len--;

        int v = last_in_path(&path);
        for (int i = 0; i < am->n; i++) {
            int cost = am->edges[v][i];
            if (cost && !vertex_in_path(&path, i)) {
                if (i == v2) {
                    cost += path_cost(&path, am);
                    if (cost < solution.cost) {
                        solution.cost = cost;
                        del_path(&solution.path);
                        solution.path = append_path_copy(&path, v2);
                    }
                } else {
                    if (queue_len == queue_max_len) {
                        struct Path* old_queue = queue;

                        queue_max_len *= 2;
                        queue = malloc(queue_max_len * sizeof(struct Path));
                        for (int j = 0; j < queue_len; j++) {
                            queue[j] = old_queue[(queue_idx + j) % queue_len];
                        }
                        queue_idx = 0;

                        free(old_queue);
                    }

                    queue[(queue_idx + queue_len) % queue_max_len] =
                        append_path_copy(&path, i);
                    queue_len++;
                }
            }
        }

        del_path(&path);
    }

    free(queue);

    return solution;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 0;
    }

    struct AdjMatrix am = parse_adj_matrix(argv[1]);

    print_adj_matrix(&am);

    srand(time(NULL));
    int v1 = rand() % am.n, v2 = rand() % am.n;

    struct Solution solution = bfs(v1, v2, &am);
    printf("\nBFS:\n");
    print_solution(&solution);

    printf("\nDFS:\n");
    print_solution(&solution);

    printf("\nDijkstra:\n");
    print_solution(&solution);

    del_adj_matrix(&am);

    return 0;
}

/*
def dfs(v1, v2, edges):
        if v1 == v2:
                return [v1], 0

        path = [v1]
        idxs = [0]
        min_cost = math.inf
        min_path = []
        while len(path) > 0:
                v = path[-1]
                idx = idxs[-1]
                adj = [edge for edge, exists in enumerate(edges[v]) if exists
and not edge in path] if idx >= len(adj): del path[-1] del idxs[-1] continue if
adj[idx] == v2: cost = path_cost(path + [v2], edges) if cost < min_cost:
                                min_cost = cost
                                min_path = path + [v2]
                idxs[-1] += 1
                path.append(adj[idx])
                idxs.append(0)

        return min_path, min_cost

def dijkstra(v1, v2, edges):
        if v1 == v2:
                return [v1], 0

        visited = [v1]
        paths = {v1: [0, []]}
        while True:
                min_cost = math.inf
                src_v = dest_v = -1
                for v in visited:
                        adj = [[edge, w] for edge, w in enumerate(edges[v]) if w
and not edge in visited] if len(adj) == 0: continue edge, w = min(adj,
key=lambda x: x[1]) if paths[v][0] + w < min_cost: min_cost = paths[v][0] + w
                                src_v = v
                                dest_v = edge
                if src_v == -1:
                        break
                paths[dest_v] = [min_cost, paths[src_v][1] + [src_v]]
                visited.append(dest_v)
                if dest_v == v2:
                        return paths[dest_v][1] + [dest_v], paths[dest_v][0]

        return [], math.inf

def test(edges, verts, func):
        sum_t = 0
        for v1, v2 in verts:
                t = time.time()
                func(v1, v2, edges)
                sum_t += time.time() - t
        print(f"Time: {sum_t*1000/len(verts)}ms")


def print_usage():
        print("Usage: python graph.py file.gr")

if __name__ == "__main__":
        if len(sys.argv) < 2:
                print_usage()
                exit(0)

        edges = parse.get_adj_matrix(sys.argv[1])
        parse.print_adj_matrix(edges)

        verts = [[randint(0, len(edges) - 1), randint(0, len(edges) - 1)] for _
in range(100)] print("BFS:") test(edges, verts, bfs) print("DFS:") test(edges,
verts, dfs) print("Dijkstra:") test(edges, verts, dijkstra)

        print()

        v1 = randint(0, len(edges) - 1)
        v2 = randint(0, len(edges) - 1)

        print(v1, v2)

        t = time.time()
        path, cost = bfs(v1, v2, edges)
        t = time.time() - t
        print(f"BFS:\nPath: {path}, Cost: {cost}\nTime: {t*1000}ms")

        t = time.time()
        path, cost = dfs(v1, v2, edges)
        t = time.time() - t
        print(f"DFS:\nPath: {path}, Cost: {cost}\nTime: {t*1000}ms")

        t = time.time()
        path, cost = dijkstra(v1, v2, edges)
        t = time.time() - t
        print(f"Dijkstra:\nPath: {path}, Cost: {cost}\nTime: {t*1000}ms")
*/
