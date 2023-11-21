#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "vertex.h"
#include "downhill_simplex.h"

/* 	
	To start, let's just think of this as an optimization problem. 
	I'll implement the algorithm, and then I'll give it some 
	arbitrary function(s) (as opposed to the error function of a NN) 
	to see if I'm able to find the minimum. This way I can test a function with 
	only 2 or 3 variables, and therefore I'll be able to visualize the algorithm, 
	using gnuplot or whatever else.
*/

int main(int argc, char **argv) {

	int N_W = 2;

/* 
	I'll define a structure for a vertex. It'll have;
	- an array of N_W indices for each dimension of the vertex
	- a double for the error associated with that vertex
	
	Then I'll define the simplex as an array of N_W+1 vertices.   
*/

	Vertex *simplex[N_W+1];
	
	for (int i = 0; i <= N_W; i++) {
      		simplex[i] = malloc(sizeof(Vertex) + N_W * sizeof(double));
   	}

/*	
	Pick N_W+1 random-ish vertices and compute the error for each 
*/	

	double w1[] = {1.2,3.1};
	double w2[] = {2.4,3.5};
	double w3[] = {6.8,7.9};	

	double e[] = {3,1,2};	
	
	vertex_put(simplex[0], w1, e[0]);
	vertex_put(simplex[1], w2, e[1]);
	vertex_put(simplex[2], w3, e[2]);

// ==============================================================
	
/*	
	Start loop
	Sort the vertices and their associated errors
*/	
	sort_simplex(simplex,N_W+1);
	
/*	
	Check termination conditions (num iterations or standard deviation)
*/	
	
/*	
	Compute the centroid of all vertices except the worst
*/

/*	
	Compute the reflected vertex
	Compute the error of the reflected vertex
	If the error of the reflected vertex is worst than the best, but better than the worst;
		replace the worst vertex with the reflected vertex and go to next loop iteration  	
*/
	
/*	
	If the error of the reflected vertex is better than the best, 
	we'll want to move further in that direction, hence expansion.
	
	So, if the error of the reflected vertex is better than the best;
		compute an expanded vertex
		compute the error of the expanded vertex  
	
		If the error of the expanded vertex is better than the error of the reflected vertex;
			replace the worst vertex with the expanded vertex and go to next loop iteration	
		Otherwise;
			replace the worst vertex with the reflected vertex and go to next loop iteration	 			
*/

/*	
	At this point in the loop it is known that the error of the reflected vertex is worst than the second worst vertex, 
	and that means the reflected vertex was placed too far away. Hence we would like to contract the vertex
	
	If the error of the refelected vertex is better than the worst vertex;
		compute a contracted vertex (outside the current simplex)
		compute the error of the contracted vertex
		
		If the error of the contracted vertex is better than the error of the reflected vertex;
			replace the worst vertex with the contracted vertex and go to next loop iteration
		Otherwise;
			continue to the next step
			
	If the error of the refelected vertex is worst than the worst vertex;
		compute a contracted vertex (inside the current simplex)
		compute the error of the contracted vertex
		
		If the error of the contracted vertex is better than the error of the worst vertex;
			replace the worst vertex with the contracted vertex and go to next loop iteration
		Otherwise;
			continue to the next step		 			
*/

/*
	Decrease the size of the simplex by replacing all the points except for the best one.
*/


	return 0;
}
