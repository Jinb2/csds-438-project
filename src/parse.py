def get_adj_matrix(graph_file):
	edges = []

	with open(graph_file, 'r') as file:
		lines = file.readlines()
		verts = lines[1]
		idx = verts.find(":")
		n = int(verts[idx+1:])
		edges = [[0] * n for _ in range(n)]
		for line in lines[8:]:
			vals = line.split()
			v1, v2 = [int(s) for s in vals[1:3]]
			edges[v1-1][v2-1] = int(vals[3])

	return edges

def print_adj_matrix(edges):
	for row in edges:
		print(row)

print_adj_matrix(get_adj_matrix("uw_10.gr"))
