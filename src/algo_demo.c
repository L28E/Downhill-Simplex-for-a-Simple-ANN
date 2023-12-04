/*
 * algo_demo.c
 *
 * A demonstration of the Nelder-Mead algorithm for a 2 variable function so that we can visualize the algorithm.
 * It'll spit out commands which can then be used to plot the simplex in Octave (or MATLAB) at each iteration
 *
 */

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "vertex.h"
#include "downhill_simplex.h"

int num_variables = 2;

double compute_error(double w[]);

int main(int argc, char **argv) {

	srand(time(NULL)); // Use current time as seed for random generator

	Vertex *simplex[num_variables + 1];
	initialize_simplex(simplex, num_variables);
	randomize_simplex(simplex, num_variables, -3, 3, compute_error);

	downhill_simplex(simplex, 1, 2, 0.5, 0.5, 0.01, 1000, 2, compute_error, compute_error, octave_print);

	return 0;
}

/*
 This function will be program specific. For a simple MLP you'd probably use MSE.
 For test purposes I'll just optimize a 2D Problem
 */
double compute_error(double w[]) {
	return pow(1-w[0],2)+100*pow(w[1]-pow(w[0],2),2);
	//return pow(w[0], 2) - 2 * w[0] + 1 + 2 * (pow(w[1], 2) - 4 * w[1] + 4);
}

