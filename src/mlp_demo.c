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

#include "vertex.h"
#include "downhill_simplex.h"

int n = 21;

int main(int argc, char **argv) {

	srand(time(NULL)); // Use current time as seed for random generator

	Vertex *simplex[n + 1];
	initialize_simplex(simplex, n);
	randomize_simplex(simplex, n, -1, 1, get_batch_training_error);

	downhill_simplex(simplex, 1, 2, 0.5, 0.5, 0.01, 1000, 21, get_batch_training_error, get_batch_validation_error, print_simplex);

	return 0;
}

/*
 * For this simple demonstration I'll just hard code the behaviour of the neural net,
 * so this function is the implementation of the MLP.
 * We have 2 inputs, 5 hidden neurons, and 1 output neuron. This gives a total of 21 weights.
 */
double get_output(double w[], double vds, double vgs) {
	double y;
	double gamma1, gamma2, gamma3, gamma4, gamma5;
	double hn1, hn2, hn3, hn4, hn5;

	// Each hidden neuron input is the weighted sum of the input layer
	gamma1 = w[0] * vds + w[1] * vgs;
	gamma2 = w[2] * vds + w[3] * vgs;
	gamma3 = w[4] * vds + w[5] * vgs;
	gamma4 = w[6] * vds + w[7] * vgs;
	gamma5 = w[8] * vds + w[9] * vgs;

	// Each hidden neuron uses a biased sigmoidal activation function
	hn1 = 1 / (1 + exp(-1 * (gamma1 - w[10])));
	hn2 = 1 / (1 + exp(-1 * (gamma2 - w[11])));
	hn3 = 1 / (1 + exp(-1 * (gamma3 - w[12])));
	hn4 = 1 / (1 + exp(-1 * (gamma4 - w[13])));
	hn5 = 1 / (1 + exp(-1 * (gamma5 - w[14])));

	// Output is the weighted sum of the hidden layer outputs and a bias
	return w[15] * hn1 + w[16] * hn2 + w[17] * hn3 + w[18] * hn4 + w[19] * hn5 + w[20];
}

double get_batch_training_error(double w[]) {
	double *y_hat = training_current;
	double *x = training_voltage;
	double y, err = 0;
	int size = training_size;

	for (int i = 0; i < size; i++) {				// VDS sweep
		for (int j = 0; j < size; j++) {			// VGS sweep
			y = get_output(w, x[i], x[j]);
			err += pow(y - y_hat[i * size + j], 2); // Squared error
		}
	}

	return err / size; // Mean Square Error
}

double get_batch_validation_error(double w[]) {
	double *y_hat = validation_current;
	double *x = validation_voltage;
	double y, err = 0;
	int size = validation_size;

	for (int i = 0; i < size; i++) {				// VDS sweep
		for (int j = 0; j < size; j++) {			// VGS sweep
			y = get_output(w, x[i], x[j]);
			err += pow(y - y_hat[i * size + j], 2); // Squared error
		}
	}

	return err / size; // Mean Square Error
}
