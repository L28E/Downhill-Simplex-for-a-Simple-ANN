#ifndef DOWNHILL_SIMPLEX_H_
#define DOWNHILL_SIMPLEX_H_

#include "vertex.h"

void sort_simplex(Vertex *simplex[], int size);
void get_centroid(Vertex *simplex[], Vertex *centroid, int size, double (*error_func)(double[]));
void get_reflected(Vertex *worst, Vertex *centroid, Vertex *reflected, int size, double alpha, double (*error_func)(double[]));
void get_expanded(Vertex *best, Vertex *centroid, Vertex *expanded, int size, double gamma, double (*error_func)(double[]));
void get_contracted(Vertex *contraction_point, Vertex *centroid, Vertex *contracted, int size, double rho, double (*error_func)(double[]));
void shrink_simplex(Vertex *simplex[], int size, double sigma, double (*error_func)(double[]));
void print_simplex(Vertex *simplex[], int size);

#endif /* DOWNHILL_SIMPLEX_H_ */
