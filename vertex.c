#include "vertex.h"

void vertex_init(Vertex *v, double *weights, double error){
	v->weights = weights;
	v->error = error;
}
