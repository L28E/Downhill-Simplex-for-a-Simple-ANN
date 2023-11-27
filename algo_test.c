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

double compute_error(double w[]); 

// Hyper parameters
const double ALPHA = 1;
const double GAMMA = 2;
const double RHO = 0.5; 	// 0 < rho < 0.5
const double SIGMA = 0.5;

int num_variables = 2;
int max_iterations = 1000;
int iteration = 0;
double tolerance = 0.01;

int main(int argc, char **argv) {	

	// Declare and allocate the simplex
	Vertex *simplex[num_variables + 1];
	for (int i = 0; i <= num_variables; i++) {
		simplex[i] = malloc(sizeof(Vertex) + num_variables * sizeof(double));
	}
	
	// Declare and allocate the vertices for updating the simplex
	Vertex *centroid = malloc(sizeof(Vertex) + num_variables * sizeof(double));
	Vertex *reflected = malloc(sizeof(Vertex) + num_variables * sizeof(double));
	Vertex *expanded = malloc(sizeof(Vertex) + num_variables * sizeof(double));
	Vertex *contracted = malloc(sizeof(Vertex) + num_variables * sizeof(double));	

	// Populate the simplex with initial vertices
	//===========================================	
	// TODO: Randomize based on search space
	double w1[] = { 3, 7 };
	double w2[] = { 2.4, 3.5 };
	double w3[] = { 6.8, 7.9 };
	double e[3] = {};		
	
	e[0] = compute_error(w1);
	e[1] = compute_error(w2);
	e[2] = compute_error(w3);
	
	// TODO: Populate simplex programmatically 
	vertex_put(simplex[0], w1, e[0], num_variables);
	vertex_put(simplex[1], w2, e[1], num_variables);
	vertex_put(simplex[2], w3, e[2], num_variables);	
	//===========================================

	while (true) {
		iteration++;	// Increment the iteration counter

		// Sort the vertices by their associated errors
		sort_simplex(simplex, num_variables + 1);
		print_simplex(simplex,num_variables);

		// Check termination conditions
		if (check_terminate(simplex,num_variables+1,tolerance) || iteration >= max_iterations) break;

		// Compute the centroid of all vertices except the worst
		get_centroid(simplex, centroid, num_variables, compute_error);
		
		// Compute the reflected vertex and its error, and replace the worst vertex with the reflected vertex if appropriate
		get_reflected(simplex[num_variables], centroid, reflected, num_variables, ALPHA, compute_error);

		if (reflected->error >= simplex[0]->error && reflected->error < simplex[num_variables - 1]->error) {
			vertex_put(simplex[num_variables], reflected->weights, reflected->error, num_variables);
			continue;
		}

		/*
		 If the error of the reflected vertex is better than the best,
		 we'll want to move further in that direction, hence expansion.

		 Compute the expanded vertex and its error, update the simplex if appropriate
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
		 and that means the reflected vertex was placed too far away and that a better value will be inside the simplex. 
		 Hence, we would like to contract the vertex.

		 Compute the contracted vertex and its error, update the simplex if appropriate
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
		
		// All else fails, decrease the size of the simplex, replacing all the points except for the best one.
		shrink_simplex(simplex, num_variables+1, SIGMA, compute_error);

	} 
	return 0;
}

/*
 This function will be program specific. For a simple MLP you'd probably use MSE.
 For test purposes I'll just optimize a 2D Problem
 */
double compute_error(double w[]) {
	return pow(w[0], 2) - 2 * w[0] + 1 + 2 * (pow(w[1], 2) - 4 * w[1] + 4);
}

