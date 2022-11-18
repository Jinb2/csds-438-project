%.o: %.c
	g++ -c $< -o $@

SRCS = parse.o graph.o
graph: main.cpp $(SRCS)
	g++ $^ -o $@
	./$@ uw_10.gr