def get_adj_matrix(v, graph_file):
	edges = [[0] * v for _ in range(v)]

	with open(graph_file, 'r') as file:
		for line in file.readlines()[8:]:
			v1, v2 = [int(s) for s in line.split()[1:3]]
			edges[v1-1][v2-1] = 1

for row in get_adj_matrix(10, "sample.gr"):
	print(row)
