from prim import Prim
import time


def get_adj_matrix(graph_file):
    edges = []

    with open(graph_file, "r") as file:
        lines = file.readlines()
        verts = lines[1]
        idx = verts.find(":")
        n = int(verts[idx + 1 :])
        edges = [[0] * n for _ in range(n)]
        for line in lines[8:]:
            vals = line.split()
            v1, v2 = [int(s) for s in vals[1:3]]
            edges[v1 - 1][v2 - 1] = int(vals[3])

    return edges


def print_adj_matrix(edges):
    for row in edges:
        print(row)


vertices = get_adj_matrix("../uw_10.gr")


print("Time to create graph and run Prim Algo")
start = time.time()
print("Start time: " + str(start))
print("---------------------------------------------------")
graph1 = Prim(
    [
        [0, 2, 0, 6, 0],
        [2, 0, 3, 8, 5],
        [0, 3, 0, 0, 7],
        [6, 8, 0, 0, 9],
        [0, 5, 7, 9, 0],
    ]
)
graph1.primMST()
end = time.time()
print("End time: " + str(end))
total = end - start
print("Total time: " + str(total) + "ms")
print("---------------------\n")

print("Time to create graph and run Prim Algo")
start = time.time()
print("Start time: " + str(start))
print("---------------------------------------------------")
graph2 = Prim(vertices)
graph2.primMST()
end = time.time()
print("End time: " + str(end))
total = (end - start) * 1000
print("Total time: " + str(total) + "ms")
print("---------------------\n")
