/*
 * mlp_demo.c
 *
 * Using the Nelder-Mead algorithm to train a very simple neural network.
 *
 * In this demonstration we train a model to represent the output of
 * a non-linear function of one variable
 *
 */

#include "simple_mlp_demo.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "vertex.h"
#include "downhill_simplex.h"

int num_hn = 2;
double min_scale_y = -1;
double max_scale_y = 1;
double min_scale_x = -1;
double max_scale_x = 1;

int main(int argc, char **argv) {

	int n = 3 * num_hn + 1;

	srand(time(NULL)); // Use output time as seed for random generator

	Vertex *simplex[n + 1];
	initialize_simplex(simplex, n);
	randomize_simplex(simplex, n, -10, 10, get_training_error);

	downhill_simplex(simplex, 1, 2, 0.5, 0.5, 0.0001, -1, n, get_training_error,
			get_validation_error, print_err);

	printf("\nSolution: ");
	print_weights(simplex, n, 0, 0);

	printf("\nOverall Test Error:  %f\n", get_test_error(simplex[0]->weights));

	print_test_error(simplex[0]->weights);

	return 0;
}

/*
 * this function is the implementation of the MLP.
 * 1 input neuron, 1 output neuron, and n hidden neurons
 * results in 3 * n + 1 variables
 */
double get_output(double w[], double x) {
	double gamma[num_hn];
	double hn[num_hn];
	double y = 0;

	for (int i = 0; i < num_hn; i++) {
		gamma[i] = w[i] * x;// Each hidden neuron input is the weighted sum of the input layer
		hn[i] = 1 / (1 + exp(-1 * (gamma[i] + w[num_hn + i]))); // Each hidden neuron uses a biased sigmoidal activation function
		y += w[2 * num_hn + i] * hn[i]; // Output is the weighted sum of the hidden layer outputs and a bias
	}
	return y + w[3 * num_hn];
}

double get_training_error(double w[]) {
	return compute_batch_error(training_size, training_output, training_input,
			training_output_min, training_output_max, w);
}

double get_validation_error(double w[]) {
	return compute_batch_error(validation_size, validation_output,
			validation_input, validation_output_min, validation_output_max, w);
}

double get_test_error(double w[]) {
	return compute_batch_error(test_size, testing_output,
			testing_input, test_output_min, test_output_max, w);
}

double compute_batch_error(int size, double output[], double input[],
		double output_min, double output_max, double w[]) {
	double err = 0;

	for (int i = 0; i < size; i++) {
		err += pow(
				(get_output(w, input[i]) - output[i])
						/ (output_max - output_min), 2);
	}
	return sqrt(err / size);
}

void print_test_error(double w[]) {
	double *y_hat = testing_output;
	double *input = testing_input;
	double x, y, err = 0;
	int size = test_size;

	for (int i = 0; i < size; i++) {
		y = get_output(w, input[i]);

		err = (y - y_hat[i]) / y_hat[i] * 100; // Percent error
		printf("Test Sample %d Error (%%): %f\n", i, err);
	}
}

