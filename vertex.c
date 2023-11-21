#include <stdlib.h>
#include <stdio.h>

#include "vertex.h"

void vertex_put(Vertex *v, double *weights, double error){
	v->weights = weights;
	v->error = error;
}

void vertex_print_weights(Vertex *v, int size){	
	printf("[");
	for (int i = 0; i < size; i++) {     
        	if (i != 0) printf(", ");
        	printf("%f", v->weights[i]);     
    	}  
    	printf("]\n");   
}

/*
 * Function:  vertex_compare 
 * --------------------
 * compares the errors of two vertices, for use in qsort()
 */
int vertex_compare(const void *a, const void *b){
	Vertex *v1 = *(Vertex **)a;
    	Vertex *v2 = *(Vertex **)b;
    	
    	if (v1->error > v2->error) {
        	return 1;
	} else if (v1->error < v2->error) {
		return -1;
	} else {
		return 0;
	}
}








