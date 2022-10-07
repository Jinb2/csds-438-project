import parse
from random import randint
import sys

def bfs(v1, v2, edges):
	if v1 == v2:
		return [v1]

	queue = [[v1]]
	while len(queue) > 0:
		path = queue[0]
		del queue[0]

		adj = [edge for edge, exists in enumerate(edges[path[-1]]) if exists and not edge in path]
		if v2 in adj:
			return path + [v2]
		queue += [path + [v] for v in adj]
	return []

def dfs(v1, v2, edges):
	if v1 == v2:
		return [v1]

	path = [v1]
	idxs = [0]
	while len(path) > 0:
		v = path[-1]
		idx = idxs[-1]
		adj = [edge for edge, exists in enumerate(edges[v]) if exists and not edge in path]
		if idx >= len(adj):
			del path[-1]
			del idxs[-1]
			continue
		if adj[idx] == v2:
			return path + [v2]
		idxs[-1] += 1
		path.append(adj[idx])
		idxs.append(0)
	return []

def dijkstra(v1, v2, edges):
	if v1 == v2:
		return [v1]

	visited = [v1]
	while True:
		for v in visited:
			adj = [edge for edge, exists in enumerate(edges[v]) is exists and not edge in visited]
				
		

def print_usage():
	print("Usage: python graph.py file.gr")

if __name__ == "__main__":
	if len(sys.argv) < 2:
		print_usage()
		exit(0)

	edges = parse.get_adj_matrix(sys.argv[1])
	parse.print_adj_matrix(edges)
	
	v1 = randint(0, 9)
	v2 = randint(0, 9)

	print(v1, v2)
	print(bfs(v1, v2, edges))
	print(dfs(v1, v2, edges))

