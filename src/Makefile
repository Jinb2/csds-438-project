%.o: %.c
	gcc -c $< -o $@

graph: graph.c parse.o
	gcc $^ -o $@
	./$@ uw_10.gr