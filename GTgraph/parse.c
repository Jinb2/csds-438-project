#include <stdio.h>
#include <stdlib.h>

// AdjMatrix
struct AdjMatrix {
	int** edges;
	int n;
};

struct AdjMatrix new_adj_matrix(int n) {
	struct AdjMatrix am;
	am.n = n;
	am.edges = malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		am.edges[i] = calloc(n, sizeof(int));
	}
	return am;
}

void del_adj_matrix(struct AdjMatrix* am) {
	for (int i = 0; i < am->n; i++) {
		free(am->edges[i]);
	}
	free(am->edges);
}

void print_adj_matrix(struct AdjMatrix* am) {
	for (int i = 0; i < am->n; i++) {
		printf("[");
		for (int j = 0; j < am->n; j++) {
			if (j != 0) {
				printf(" ");
			}
			printf("%d", am->edges[i][j]);
		}
		printf("]\n");
	}
}

struct AdjMatrix parse_adj_matrix(const char* graph_file) {
    FILE* file = fopen(graph_file, "r");

    char line[256];

    // Skip to line 2
    int i = 0;
    for (; i < 2; i++) {
        fgets(line, sizeof(line), file);
    }

    int n = 10;
	struct AdjMatrix am = new_adj_matrix(n);

    // Skip to line 8
    for (; i < 8; i++) {
        fgets(line, sizeof(line), file);
    }

    // Get the next n vertices
    while(fgets(line, sizeof(line), file)) {
        for (int j = 0; j < 256; j++) {
            if (line[j] == ' ') {
            	char* p = &line[j];
                int v1 = strtoul(p, &p, 10) - 1;
				int v2 = strtoul(p, &p, 10) - 1;
				int w = strtoul(p, &p, 10);
				am.edges[v1][v2] = w;
                break;
			}
        }
    }

	return am;
}

int main(int argc, char* argv[]) {
	struct AdjMatrix am = parse_adj_matrix(argv[1]);

	print_adj_matrix(&am);

	del_adj_matrix(&am);

	return 0;
}

