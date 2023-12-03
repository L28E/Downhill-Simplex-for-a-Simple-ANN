#include <stdlib.h>
#include <stdio.h>

#include "downhill_simplex.h"
#include "vertex.h"

/*
 * Function:  downhill_simplex
 * --------------------
 * Executes the Nelder–Mead method. Moves a simplex through the variable space towards the minimum of the given function(s).
 *
 * *simplex[]: A pointer array, pointing to the vertices of the simplex. A simplex by definition should have one more vertex than the number of variables
 * alpha: Reflection hyperparameter
 * gamma: Expansion hyperparameter
 * rho: Contraction hyperparameter
 * sigma: Shrinkage hyperparameter
 * tolerance: The minimum acceptable validation error, used to determine whether training should continue
 * max_iterations: The maximum number of iterations
 * num_variables: The number of variables in the given optimization problem
 * training_error_func: Pointer to the function which calculates training error
 * validation_error_func:  Pointer to the function which calculates validation error
 * print_func: Pointer to the function which runs immediately after sorting the simplex (a good place to print out the simplex)
 *
 */
void downhill_simplex(Vertex *simplex[], double alpha, double gamma, double rho,
		double sigma, double tolerance, double max_iterations,
		int num_variables, double (*training_error_func)(double[]),
		double (*validation_error_func)(double[]),
		void (*print_func)(Vertex *simplex[], int size, int iteration)) {

	int iteration = 0;

	// Declare and allocate the vertices for updating the simplex
	Vertex *centroid = malloc(sizeof(Vertex) + num_variables * sizeof(double));
	Vertex *reflected = malloc(sizeof(Vertex) + num_variables * sizeof(double));
	Vertex *expanded = malloc(sizeof(Vertex) + num_variables * sizeof(double));
	Vertex *contracted = malloc(sizeof(Vertex) + num_variables * sizeof(double));

	while (true) {
		iteration++;	// Increment the iteration counter

		// Sort the vertices by their associated errors
		sort_simplex(simplex, num_variables + 1);
		print_func(simplex, num_variables, iteration);

		// Check termination conditions
		if (check_terminate(simplex, num_variables + 1, tolerance, validation_error_func) || iteration >= max_iterations)
			break;

		// Compute the centroid of all vertices except the worst
		get_centroid(simplex, centroid, num_variables, training_error_func);

		// Compute the reflected vertex and its error, and replace the worst vertex with the reflected vertex if appropriate
		get_reflected(simplex[num_variables], centroid, reflected,
				num_variables, alpha, training_error_func);

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
			get_expanded(simplex[0], centroid, expanded, num_variables, gamma, training_error_func);
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
		if (reflected->error < simplex[num_variables]->error) {
			get_contracted(reflected, centroid, contracted, num_variables, rho,
					training_error_func);
			if (contracted->error < reflected->error) {
				vertex_put(simplex[num_variables], contracted->weights, contracted->error, num_variables);
				continue;
			}
		} else if (reflected->error >= simplex[num_variables]->error) {
			get_contracted(simplex[num_variables], centroid, contracted, num_variables, rho, training_error_func);
			if (contracted->error < simplex[num_variables]->error) {
				vertex_put(simplex[num_variables], contracted->weights, contracted->error, num_variables);
				continue;
			}
		}

		// All else fails, decrease the size of the simplex, replacing all the points except for the best one.
		shrink_simplex(simplex, num_variables + 1, sigma, training_error_func);

	}
}

/*
 * Function:  initialize_simplex
 * --------------------
 * Allocates enough memory for the simplex
 *
 */
void initialize_simplex(Vertex *simplex[], int size) {
	for (int i = 0; i <= size; i++) {
		simplex[i] = malloc(sizeof(Vertex) + size * sizeof(double));
	}
}

/*
 * Function:  randomize_simplex
 * --------------------
 * Populates the simplex with initial vertices.
 * i.e. generates size+1 vectors of size random values between the given min and max
 *
 */
void randomize_simplex(Vertex *simplex[], int size, double min, double max,
		double (*training_error_func)(double[])) {
	double w[size];
	double err;

	for (int i = 0; i < size + 1; i++) {
		for (int j = 0; j < size; j++) {
			w[j] = random_double(min, max);
		}
		err = training_error_func(w);
		vertex_put(simplex[i], w, err, size);
	}
}

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
void get_centroid(Vertex *simplex[], Vertex *centroid, int size,
		double (*error_func)(double[])) {
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
void get_reflected(Vertex *worst, Vertex *centroid, Vertex *reflected, int size,
		double alpha, double (*error_func)(double[])) {
	double weights[size];
	double error;

	for (int i = 0; i < size; i++) {
		weights[i] = centroid->weights[i]
				+ alpha * (centroid->weights[i] - worst->weights[i]);
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
void get_expanded(Vertex *best, Vertex *centroid, Vertex *expanded, int size,
		double gamma, double (*error_func)(double[])) {
	double weights[size];
	double error;

	for (int i = 0; i < size; i++) {
		weights[i] = centroid->weights[i]
				+ gamma * (best->weights[i] - centroid->weights[i]);
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
void get_contracted(Vertex *contraction_point, Vertex *centroid,
		Vertex *contracted, int size, double rho,
		double (*error_func)(double[])) {
	double weights[size];
	double error;

	for (int i = 0; i < size; i++) {
		weights[i] = centroid->weights[i]
				+ rho * (contraction_point->weights[i] - centroid->weights[i]);
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
void shrink_simplex(Vertex *simplex[], int size, double sigma,
		double (*error_func)(double[])) {
	double weights[size];
	double error;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			weights[j] = simplex[0]->weights[j]
					+ sigma * (simplex[i]->weights[j] - simplex[0]->weights[j]);
		}

		error = error_func(weights);
		vertex_put(simplex[i], weights, error, size);
	}
}

/*
 * Function:  check_terminate_simple
 * --------------------
 * If all errors in the simplex are below the tolerance, return true.
 * Otherwise return false.
 *
 */
bool check_terminate_simple(Vertex *simplex[], int size, double tolerance) {

	for (int i = 0; i < size; i++) {
		if (simplex[i]->error >= tolerance)
			return false;
	}

	return true;
}

/*
 * Function:  check_terminate
 * --------------------
 * Checks the tolerance against the validation error, as opposed to the training error.
 * That means it has to be computed for each vector in the simplex
 *
 */
bool check_terminate(Vertex *simplex[], int size, double tolerance,
	double (*validation_error_func)(double[])) {

	for (int i = 0; i < size; i++) {
		if (validation_error_func(simplex[i]->weights) >= tolerance)
			return false;
	}

	return true;
}

/*
 * Function:  print_simplex
 * --------------------
 * pretty print the simplex
 *
 */
void print_simplex(Vertex *simplex[], int size, int iteration) {

	// Printing weights
	printf("[");
	for (int i = 0; i < size + 1; i++) {
		for (int j = 0; j < size; j++) {
			if (j == 0)
				printf("[ ");
			if (j != 0)
				printf(", ");

			printf("%f", simplex[i]->weights[j]);

			if (j == size - 1) {
				if (i != size) {
					printf("], ");
				} else {
					printf("]");
				}
			}
		}
	}
	printf("], ");

	// Printing errors
	for (int i = 0; i < size + 1; i++) {
		if (i != 0)
			printf(", ");
		printf("%f ", simplex[i]->error);
	}
	printf("\n");
}

/*
 * Function:  octave_print
 * --------------------
 * Formulates MATLAB/Octave vectors to plot the current simplex
 * ONLY SUITABLE FOR 2 VARIABLE PROBLEMS
 *
 */

void octave_print(Vertex *simplex[], int size, int iteration) {	
	for (int i = 0; i < size; i++) {
		if (i == 0){
			printf("X(%d,:)=[ ", iteration);
		}else if (i == 1){
			printf("Y(%d,:)=[ ", iteration);
		}

		for (int j = 0; j < size + 1; j++) {
			printf("%f ", simplex[j]->weights[i]);
			if (j == size)
				printf("%f ", simplex[0]->weights[i]); // Print out the first weight again to complete the triangle when plotting
		}
		printf("];\n");
	}	
}

/*
 * Function:  print_err
 * --------------------
 * Print the iteration and the current best training error
 *
 */

void print_err(Vertex *simplex[], int size, int iteration){
	printf("Iteration: %d, Error: %E\n",iteration,simplex[0]->error);
}

/*
 * Function:  random_double
 * --------------------
 * Generates a random double between the given minimum and maximum
 *
 */
double random_double(double min, double max) {
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}
