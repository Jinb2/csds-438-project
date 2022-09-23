import parse
from random import randint

def bfs(v1, v2, edges):
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
	path = [[v1, 0]]
	while len(path) > 0:
		v, idx = path[-1]
		adj = [edge for edge, exists in enumerate(edges[v]) if exists and not edge in path]
		if idx >= len(adj):
			del path[-1]
			continue
		if adj[idx] == v2:
			return [p[0] for p in path] + [v2]
		path[-1][1] += 1
		path.append([adj[idx], 0])

	return []

if __name__ == "__main__":
	edges = parse.get_adj_matrix(10, "sample.gr")
	parse.print_adj_matrix(edges)
	
	v1 = randint(0, 9)
	v2 = randint(0, 9)

	print(v1, v2)
	print(bfs(v1, v2, edges))
	print(dfs(v1, v2, edges))

