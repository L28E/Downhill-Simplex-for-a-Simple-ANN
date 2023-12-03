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

int num_hn = 4;
double min_scale_y = -1;
double max_scale_y = 1;
double min_scale_x = -1;
double max_scale_x = 1;

int main(int argc, char **argv) {

	int n = 4 * num_hn + 1;

	srand(time(NULL)); // Use current time as seed for random generator

	Vertex *simplex[n + 1];
	initialize_simplex(simplex, n);
	randomize_simplex(simplex, n, -1, 1, get_training_error);

	downhill_simplex(simplex, 1, 2, 0.5, 0.5, 0.01, 1E6, n,
			get_training_error, get_validation_error, print_err);

	//print_test_error(simplex[0]->weights);

	return 0;
}

double scale(double x, double x_min, double x_max, double x_hat_min, double x_hat_max){
	return x_hat_min + (x - x_min) / (x_max - x_min) * (x_hat_max - x_hat_min);
}

double unscale(double x_hat, double x_hat_min, double x_hat_max, double x_min, double x_max){
	return x_min + (x_hat - x_hat_min) / (x_hat_max - x_hat_min) * (x_max - x_min);
}

/*
 * this function is the implementation of the MLP.
 * 2 input neurons, 1 output neuron, and n hidden neurons
 * results in 4 * n + 1 variables
 */
double get_output(double w[], double x1, double x2) {
	double gamma[num_hn];
	double hn[num_hn];
	double y = 0;

	for (int i = 0; i < num_hn; i++) {
		gamma[i] = w[2 * i] * x1 + w[2 * i + 1] * x2;	// Each hidden neuron input is the weighted sum of the input layer
		hn[i] = 1 / (1 + exp(-1 * (gamma[i] - w[num_hn*2+i]))); // Each hidden neuron uses a biased sigmoidal activation function
		y += w[3 * num_hn + i] * hn[i]; // Output is the weighted sum of the hidden layer outputs and a bias
	}
	return y + w[4*num_hn];
}

double get_training_error(double w[]) {
	return compute_batch_error(training_size, max_scale_y, min_scale_y,
			training_current, training_voltage, training_voltage_min,
			training_voltage_max, training_current_min, training_current_max, w);
}

double get_validation_error(double w[]) {
	return compute_batch_error(validation_size, max_scale_y, min_scale_y,
			validation_current, validation_voltage, validation_voltage_min,
			validation_voltage_max, validation_current_min,
			validation_current_max, w);
}

double compute_batch_error(int size, double y_max, double y_min,
		double output[], double input[], double input_min,
		double input_max, double output_min, double output_max, double w[]) {
	double y, y_hat, x1, x2, err = 0;

	for (int i = 0; i < size; i++) {					// VDS sweep
		for (int j = 0; j < size; j++) {			// VGS sweep
			// Scale each input
			x1 = scale(input[i],input_min,input_max,min_scale_x,max_scale_x);
			x2 = scale(input[j],input_min,input_max,min_scale_x,max_scale_x);

			// Scale the measured output, but not the computed output
			y = get_output(w, x1, x2);
			y_hat = scale(output[i * size + j],output_min,output_max,min_scale_y,max_scale_y);

			err += pow((y - y_hat) / (y_max - y_min), 2);
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
