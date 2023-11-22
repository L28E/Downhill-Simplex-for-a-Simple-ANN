#ifndef DOWNHILL_SIMPLEX_H_
#define DOWNHILL_SIMPLEX_H_

#include "vertex.h"

void sort_simplex(Vertex *simplex[], int size);
void find_centroid(Vertex *simplex[], Vertex *centroid, int size, double (*error_func)(double[]));

#endif /* DOWNHILL_SIMPLEX_H_ */
