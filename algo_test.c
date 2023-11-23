#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

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

/*
 This function will be program specific. For a simple MLP you'd probably use MSE.
 For test purposes I'll just optimize a 2D Problem
 */
double compute_error(double w[]) {
	return pow(w[0], 2) - 2 * w[0] + 1 + 2 * (pow(w[1], 2) - 4 * w[1] + 4);
}

// Hyper parameters
const double ALPHA = 1;
const double GAMMA = 2;
const double RHO = 0.5; 	// 0 < rho < 0.5
const double SIGMA = 0.5;

int main(int argc, char **argv) {

	int num_variables = 2;
	int max_iterations = 1000;
	bool continue_training = true;

	// Declare and allocate the simplex
	Vertex *simplex[num_variables + 1];

	for (int i = 0; i <= num_variables; i++) {
		simplex[i] = malloc(sizeof(Vertex) + num_variables * sizeof(double));
	}

	/*
	 Pick num_variables+1 random or random-ish vertices in the search space
	 and compute the error for each
	 */

	// TODO: Randomize based on search space
	double w1[] = { 3, 7 };
	double w2[] = { 2.4, 3.5 };
	double w3[] = { 6.8, 7.9 };

	double e[3] = {};

	e[0] = compute_error(w1);
	e[1] = compute_error(w2);
	e[2] = compute_error(w3);

	vertex_put(simplex[0], w1, e[0], num_variables);
	vertex_put(simplex[1], w2, e[1], num_variables);
	vertex_put(simplex[2], w3, e[2], num_variables);

	print_simplex(simplex,num_variables);

	Vertex *centroid = malloc(sizeof(Vertex) + num_variables * sizeof(double));
	Vertex *reflected = malloc(sizeof(Vertex) + num_variables * sizeof(double));
	Vertex *expanded = malloc(sizeof(Vertex) + num_variables * sizeof(double));
	Vertex *contracted = malloc(sizeof(Vertex) + num_variables * sizeof(double));

	while (continue_training) {
		// Sort the vertices and their associated errors
		sort_simplex(simplex, num_variables + 1);
		print_simplex(simplex,num_variables);

		// TODO: Check termination conditions (num iterations or standard deviation)

		// Compute the centroid of all vertices except the worst
		get_centroid(simplex, centroid, num_variables, compute_error);

		/*
		 Compute the reflected vertex
		 Compute the error of the reflected vertex
		 If the error of the reflected vertex is worst than the best, but better than the SECOND worst;
		 replace the worst vertex with the reflected vertex and go to next loop iteration
		 */
		get_reflected(simplex[num_variables], centroid, reflected, num_variables, ALPHA, compute_error);

		if (reflected->error >= simplex[0]->error && reflected->error < simplex[num_variables - 1]->error) {
			vertex_put(simplex[num_variables], reflected->weights, reflected->error, num_variables);
			continue;
		}

		/*
		 If the error of the reflected vertex is better than the best,
		 we'll want to move further in that direction, hence expansion.

		 So, if the error of the reflected vertex is better than the best;
		 compute an expanded vertex
		 compute the error of the expanded vertex

		 If the error of the expanded vertex is better than the error of the reflected vertex;
		 replace the worst vertex with the expanded vertex and go to next loop iteration
		 Otherwise;
		 replace the worst vertex with the reflected vertex and go to next loop iteration
		 */
		if (reflected->error < simplex[0]->error) {
			get_expanded(simplex[0], centroid, expanded, num_variables, GAMMA, compute_error);
			if (expanded->error < reflected->error) {
				vertex_put(simplex[num_variables], expanded->weights, expanded->error, num_variables);
				continue;
			} else {
				vertex_put(simplex[num_variables], reflected->weights, reflected->error, num_variables);
				continue;
			}
		}

		/*
		 At this point in the loop it is known that the error of the reflected vertex is worst than the second worst vertex,
		 and that means the reflected vertex was placed too far away. Hence we would like to contract the vertex

		 If the error of the reflected vertex is better than the worst vertex;
		 compute a contracted vertex (outside the current simplex)
		 compute the error of the contracted vertex

			 If the error of the contracted vertex is better than the error of the reflected vertex;
			 	 replace the worst vertex with the contracted vertex and go to next loop iteration
			 Otherwise;
			 	 continue to the next step

		 If the error of the reflected vertex is worst than the worst vertex;
		 compute a contracted vertex (inside the current simplex)
		 compute the error of the contracted vertex

			 If the error of the contracted vertex is better than the error of the worst vertex;
			 	 replace the worst vertex with the contracted vertex and go to next loop iteration
			 Otherwise;
			 	 continue to the next step
		 */
		if (reflected->error < simplex[num_variables]->error){
			get_expanded(reflected, centroid, contracted, num_variables, RHO, compute_error);
			if (contracted->error < reflected->error) {
				vertex_put(simplex[num_variables], contracted->weights, contracted->error, num_variables);
				continue;
			}
		}else if (reflected->error >= simplex[num_variables]->error){
			get_expanded(simplex[num_variables], centroid, contracted, num_variables, RHO, compute_error);
			if (reflected->error < simplex[num_variables]->error) {
				vertex_put(simplex[num_variables], contracted->weights, contracted->error, num_variables);
				continue;
			}
		}

		/*
		 All else fails, decrease the size of the simplex, replacing all the points except for the best one.
		 */
		shrink_simplex(simplex, num_variables+1, SIGMA, compute_error);

		continue_training = false;
	} // training loop
	return 0;
}
