#ifndef DOWNHILL_SIMPLEX_H_
#define DOWNHILL_SIMPLEX_H_

#include "vertex.h"
#include <stdbool.h>

void initialize_simplex(Vertex *simplex[], int size);
void sort_simplex(Vertex *simplex[], int size);
void get_centroid(Vertex *simplex[], Vertex *centroid, int size, double (*error_func)(double[]));
void get_reflected(Vertex *worst, Vertex *centroid, Vertex *reflected, int size, double alpha, double (*error_func)(double[]));
void get_expanded(Vertex *best, Vertex *centroid, Vertex *expanded, int size, double gamma, double (*error_func)(double[]));
void get_contracted(Vertex *contraction_point, Vertex *centroid, Vertex *contracted, int size, double rho, double (*error_func)(double[]));
void shrink_simplex(Vertex *simplex[], int size, double sigma, double (*error_func)(double[]));
void print_simplex(Vertex *simplex[], int size);
bool check_terminate_simple(Vertex *simplex[], int size, double tolerance);
double random_double(double min, double max);
void downhill_simplex(Vertex *simplex[], double alpha, double gamma, double rho, double sigma, double tolerance, double max_iterations, int num_variables, double (*training_error_func)(double[]), double (*validation_error_func)(double[]));

#endif /* DOWNHILL_SIMPLEX_H_ */
