import parse
from random import randint
import sys
import math
import time

def path_cost(path, edges):
	return sum([edges[v1][v2] for v1, v2 in zip(path[:-1], path[1:])])

def bfs(v1, v2, edges):
	if v1 == v2:
		return [v1], 0

	queue = [[v1]]
	while len(queue) > 0:
		path = queue[0]
		del queue[0]

		adj = [edge for edge, exists in enumerate(edges[path[-1]]) if exists and not edge in path]
		if v2 in adj:
			return path + [v2], path_cost(path + [v2], edges)
		queue += [path + [v] for v in adj]
	
	return [], math.inf

def dfs(v1, v2, edges):
	if v1 == v2:
		return [v1], 0

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
			return path + [v2], path_cost(path + [v2], edges)
		idxs[-1] += 1
		path.append(adj[idx])
		idxs.append(0)
	
	return [], math.inf

def dijkstra(v1, v2, edges):
	if v1 == v2:
		return [v1], 0

	visited = [v1]
	paths = {v1: [0, []]}
	while True:
		min_cost = math.inf
		src_v = dest_v = -1
		for v in visited:
			adj = [[edge, w] for edge, w in enumerate(edges[v]) if w and not edge in visited]
			if len(adj) == 0:
				continue
			edge, w = min(adj, key=lambda x: x[1])
			if paths[v][0] + w < min_cost:
				min_cost = paths[v][0] + w
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
	
	verts = [[randint(0, len(edges) - 1), randint(0, len(edges) - 1)] for _ in range(100)]
	print("BFS:")
	test(edges, verts, bfs)
	print("DFS:")
	test(edges, verts, dfs)
	print("Dijkstra:")
	test(edges, verts, dijkstra)

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


