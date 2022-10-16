%.o: %.c
	gcc -c $< -o $@

SRCS = parse.o path.o solution.o
graph: graph.c $(SRCS)
	gcc $^ -o $@
	./$@ uw_10.gr