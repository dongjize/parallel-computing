﻿#include <cstdio>
#include <iostream>
#include <omp.h>


#define MAX 10000
#define NOT_CONNECTED -1

int distance[MAX][MAX];

int nodesCount;

int main(int argc, char** argv) {

	double wall_time = omp_get_wtime();

	int numThreads = omp_get_max_threads();

	if (argc != 2) {
		printf("The path to the input file is not specified as a parameter.\n");
		return -1;
	}
	FILE *in_file = fopen(argv[1], "r");
	if (in_file == NULL)
	{
		printf("Can't open file for reading.\n");
		return -1;
	}


#pragma omp parallel for num_threads(numThreads)
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			distance[i][j] = NOT_CONNECTED;

		}
		distance[i][i] = 0;
	}

	fscanf(in_file, "%d", &nodesCount);

#pragma omp barrier

	int a, b, c;
	while (fscanf(in_file, "%d %d %d", &a, &b, &c) != EOF) {
		if (a > nodesCount || b > nodesCount) {
			printf("Vertex index out of boundary.");
			return -1;
		}
		distance[a][b] = c;
	}

	//Floyd-Warshall
	for (int k = 1; k <= nodesCount; ++k) {
#pragma omp parallel for num_threads(numThreads)
		for (int i = 1; i <= nodesCount; ++i) {
			if (distance[i][k] != NOT_CONNECTED) {
				for (int j = 1; j <= nodesCount; ++j) {
					if (distance[k][j] != NOT_CONNECTED && (distance[i][j] == NOT_CONNECTED || distance[i][k] + distance[k][j] < distance[i][j])) {
						distance[i][j] = distance[i][k] + distance[k][j];
					}
				}
			}

		}
	}


	int diameter = -1;
	//look for the most distant pair
#pragma omp parallel for num_threads(numThreads)
	for (int i = 1; i <= nodesCount; ++i) {
		for (int j = 1; j <= nodesCount; ++j) {
			if (diameter < distance[i][j]) {
				diameter = distance[i][j];
				//printf("%d-%d-%d\n", i, diameter, j);
			}
		}
	}

	printf("%d\n", diameter);

	std::cout << "Running time is: " << omp_get_wtime() - wall_time << "s" << std::endl;

	return 0;

}