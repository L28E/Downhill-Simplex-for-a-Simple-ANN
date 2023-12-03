/*
 * mlp_demo.c
 *
 * Using the Nelder-Mead algorithm to train a very simple neural network.
 *
 * In this demonstration we train a model to represent the current of
 * a minimum sized nmos1v from the GPDK45 kit as a function of the gate-source
 * voltage and the drain-source voltage.
 *
 */

#include "mlp_demo.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#include "vertex.h"
#include "downhill_simplex.h"

int num_hn = 25;

int main(int argc, char **argv) {

	int n = 4 * num_hn + 1;

	srand(time(NULL)); // Use current time as seed for random generator

	Vertex *simplex[n + 1];
	initialize_simplex(simplex, n);
	randomize_simplex(simplex, n, -10, 10, get_batch_training_error);

	downhill_simplex(simplex, 1, 2, 0.5, 0.5, 0.01, 1E6, n,
			get_batch_training_error, get_batch_validation_error, print_err);

	print_test_error(simplex[0]->weights);

	return 0;
}

/*
 * this function is the implementation of the MLP.
 * 2 input neurons, 1 output neuron, and a dynamic number of hidden neurons
 */
double get_output(double w[], double vds, double vgs) {
	double gamma[num_hn];
	double hn[num_hn];
	double y = 0;

	for (int i = 0; i < num_hn; i++) {
		gamma[i] = w[2 * i] * vds + w[2 * i + 1] * vgs;	// Each hidden neuron input is the weighted sum of the input layer
		hn[i] = 1 / (1 + exp(-1 * (gamma[i] - w[num_hn*2+i]))); // Each hidden neuron uses a biased sigmoidal activation function
		y += w[3 * num_hn + i] * hn[i]; // Output is the weighted sum of the hidden layer outputs and a bias
	}
	return y + w[4*num_hn];
}

double get_batch_training_error(double w[]) {
	double *y_hat = training_current;
	double *x = training_voltage;
	double y, err = 0;
	double y_min = training_current_min;
	double y_max = training_current_max;
	int size = training_size;

	for (int i = 0; i < size; i++) {				// VDS sweep
		for (int j = 0; j < size; j++) {			// VGS sweep
			y = get_output(w, x[i], x[j]);
			err += pow((y - y_hat[i * size + j])/(y_max-y_min), 2);
		}
	}

	return sqrt(err / size);
}

double get_batch_validation_error(double w[]) {
	double *y_hat = validation_current;
	double *x = validation_voltage;
	double y, err = 0;
	double y_min = validation_current_min;
	double y_max = validation_current_max;
	int size = validation_size;

	for (int i = 0; i < size; i++) {				// VDS sweep
		for (int j = 0; j < size; j++) {			// VGS sweep
			y = get_output(w, x[i], x[j]);
			err += pow((y - y_hat[i * size + j])/(y_max-y_min), 2);
		}
	}

	return sqrt(err / size);
}

void print_test_error(double w[]) {
	// TODO: Correct this calculation
	double *y_hat = test_current;
	double *x = test_voltage;
	double y, err = 0;
	int size = test_size;

	for (int i = 0; i < size; i++) {				// VDS sweep
		for (int j = 0; j < size; j++) {			// VGS sweep
			y = get_output(w, x[i], x[j]);
			err = (y - y_hat[i * size + j]) / y_hat[i * size + j] * 100; // Percent error
			printf("Test Sample %d Error (%%): %f\n", i * size + j + 1, err);
		}
	}
}
