#include <stdlib.h>
#include <stdio.h>

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
 * Function:  get_centroid 
 * --------------------
 * Computes the centroid of the simplex, omitting the last (and therefore the worst) vertex
 * 
 */
void get_centroid(Vertex *simplex[], Vertex *centroid, int size, double (*error_func)(double[])) {
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

/*
 * Function:  get_reflected 
 * --------------------
 * Computes the reflected vertex
 * 
 */
void get_reflected(Vertex *worst, Vertex *centroid, Vertex *reflected, int size, double alpha, double (*error_func)(double[])) {
	double weights[size];
	double error;

	for (int i = 0; i < size; i++) {
		weights[i]=centroid->weights[i]+alpha*(centroid->weights[i]-worst->weights[i]);
	}

	error = error_func(weights);
	vertex_put(reflected, weights, error, size);
}

/*
 * Function:  get_expanded
 * --------------------
 * Computes the expanded vertex
 *
 */
void get_expanded(Vertex *best, Vertex *centroid, Vertex *expanded, int size, double gamma, double (*error_func)(double[])) {
	double weights[size];
	double error;

	for (int i = 0; i < size; i++) {
		weights[i]=centroid->weights[i]+gamma*(best->weights[i]-centroid->weights[i]);
	}

	error = error_func(weights);
	vertex_put(expanded, weights, error, size);
}

/*
 * Function:  get_contracted
 * --------------------
 * Computes a contracted vertex
 *
 */
void get_contracted(Vertex *contraction_point, Vertex *centroid, Vertex *contracted, int size, double rho, double (*error_func)(double[])) {
	double weights[size];
	double error;

	for (int i = 0; i < size; i++) {
		weights[i]=centroid->weights[i]+rho*(contraction_point->weights[i]-centroid->weights[i]);
	}

	error = error_func(weights);
	vertex_put(contracted, weights, error, size);
}

/*
 * Function:  shrink_simplex
 * --------------------
 * Computes a shrunken simplex
 *
 */
void shrink_simplex(Vertex *simplex[], int size, double sigma, double (*error_func)(double[])) {
	double weights[size];
	double error;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			weights[j]=simplex[0]->weights[j]+sigma*(simplex[i]->weights[j]-simplex[0]->weights[j]);
		}

		error = error_func(weights);
		vertex_put(simplex[i], weights, error, size);
	}
}


/*
 * Function:  print_simplex
 * --------------------
 * pretty print the simplex
 *
 */
void print_simplex(Vertex *simplex[], int size) {

	// Printing weights
	printf("[");
	for (int i = 0; i < size+1; i++) {
		for (int j = 0; j < size; j++){
			if (j == 0) printf("[ ");
			if (j != 0) printf(", ");

			printf("%f", simplex[i]->weights[j]);

			if (j == size-1){
				if (i != size){
					printf("], ");
				} else{
					printf("]");
				}
			}
		}
	}
	printf("], ");

	// Printing errors
	for (int i = 0; i < size+1; i++) {
		if (i != 0) printf(", ");
		printf("%f ",simplex[i]->error);
	}
	printf("\n");
}

