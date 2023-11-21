#include <stdlib.h>

#include "downhill_simplex.h"
#include "vertex.h"

/*
 * Function:  sort_simplex 
 * --------------------
 * Sorts the simplex by ascending error using qsort from the standard library. 
 * 
 */
void sort_simplex(Vertex *simplex[], int size){ 
	qsort(simplex, size, sizeof(simplex[0]), vertex_compare);	
}


