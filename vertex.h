#ifndef VERTEX_H_
#define VERTEX_H_

typedef struct {
	double *weights;
	double error;
} Vertex;

void vertex_init(Vertex *v, double *weights, double error);

#endif /* VERTEX_H_ */
