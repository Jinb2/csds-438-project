graph_omp.o: graph_omp.cpp
	g++ -fopenmp -std=c++11 -c $< -o $@	

%.o: %.c
	g++ -std=c++11 -c $< -o $@

%_serial: %.cpp parse.o graph.o
	g++ -std=c++11 $^ -o $@

%_omp: %.cpp parse.o graph_omp.o
	g++ -fopenmp -std=c++11 $^ -o $@
