#include <stdlib.h>

#include "downhill_simplex.h"
#include "vertex.h"

/*
 * Function:  sort_simplex 
 * --------------------
 * Sorts the simplex by ascending error using qsort from the standard library. 
 * 
 */
void sort_simplex(Vertex *simplex[], int size) {
	qsort(simplex, size, sizeof(simplex[0]), vertex_compare);
}

/*
 * Function:  find_centroid 
 * --------------------
 * Computes and returns the centroid of the simplex, omitting the last (and therefore the worst) vertex
 * 
 */
void find_centroid(Vertex *simplex[], Vertex *centroid, int size, double (*error_func)(double[])) {
	double weights[size];
	double error;

	for (int i = 0; i < size; i++) {
		weights[i] = 0;
		for (int j = 0; j < size; j++) {
			weights[i] += simplex[j]->weights[i];
		}
		weights[i] /= size;
	}

	error = error_func(weights);
	vertex_put(centroid, weights, error, size);
}

