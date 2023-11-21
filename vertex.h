#ifndef VERTEX_H_
#define VERTEX_H_

typedef struct {
	double *weights;
	double error;
} Vertex;

void vertex_put(Vertex *v, double *weights, double error);
void vertex_print_weights(Vertex *v, int size);
int vertex_compare(const void *a, const void *b);

#endif /* VERTEX_H_ */
