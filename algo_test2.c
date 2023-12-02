#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "vertex.h"
#include "downhill_simplex.h"

/* 	
 To start, let's just think of this as an optimization problem.
 I'll implement the algorithm, and then I'll give it some
 arbitrary function(s) (as opposed to the error function of a NN)
 to see if I'm able to find the minimum. This way I can test a function with
 only 2 or 3 variables, and therefore I'll be able to visualize the algorithm,
 using gnuplot or whatever else.
 */

int num_variables = 2;

double compute_error(double w[]);

int main(int argc, char **argv) {

	// Declare and allocate the simplex
	Vertex *simplex[num_variables + 1];
	initialize_simplex(simplex, num_variables);

	double w[num_variables];
	double err;
	srand(time(0)); // Use current time as seed for random generator

	// Populate the simplex with initial vertices. Generate n+1 vectors of n small random values
	for (int i = 0; i < num_variables + 1; i++) {
		for (int j = 0; j < num_variables; j++) {
			w[j] = random_double(-10, 10);
		}
		err = compute_error(w);
		vertex_put(simplex[i], w, err, num_variables);
	}

	downhill_simplex(simplex, 1, 2, 0.5, 0.5, 0.01, 1000, 2, compute_error, compute_error);

	return 0;
}

/*
 This function will be program specific. For a simple MLP you'd probably use MSE.
 For test purposes I'll just optimize a 2D Problem
 */
double compute_error(double w[]) {
	return pow(w[0], 2) - 2 * w[0] + 1 + 2 * (pow(w[1], 2) - 4 * w[1] + 4);
}

