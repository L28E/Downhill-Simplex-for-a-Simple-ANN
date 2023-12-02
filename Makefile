CC ?= gcc

all: demo_mlp algo_test algo_test2

# ============================================
# Compile and build the algorithm test 
# ============================================
demo_mlp: demo_mlp.o vertex.o downhill_simplex.o
	$(CC) -o demo_mlp.out demo_mlp.o vertex.o downhill_simplex.o -lm

algo_test: algo_test.o vertex.o downhill_simplex.o
	$(CC) -o algo_test.out algo_test.o vertex.o downhill_simplex.o -lm

algo_test2: algo_test2.o vertex.o downhill_simplex.o
	$(CC) -o algo_test2.out algo_test2.o vertex.o downhill_simplex.o -lm

demo_mlp.o: demo_mlp.c demo_mlp.h vertex.h downhill_simplex.h
	$(CC) -c demo_mlp.c

algo_test.o: algo_test.c vertex.h downhill_simplex.h
	$(CC) -c algo_test.c

algo_test2.o: algo_test2.c vertex.h downhill_simplex.h
	$(CC) -c algo_test2.c
	
vertex.o: vertex.c vertex.h
	$(CC) -c vertex.c 
	
downhill_simplex.o: downhill_simplex.c downhill_simplex.h vertex.h
	$(CC) -c downhill_simplex.c 	

# ============================================
# Debug: compile with the -g tag
# ============================================
debug_demo_mlp: demo_mlp_debug.o vertex_debug.o downhill_simplex_debug.o
	$(CC) -o demo_mlp_debug.out demo_mlp_debug.o vertex_debug.o downhill_simplex_debug.o -g -lm

debug_algo_test: algo_test_debug.o vertex_debug.o downhill_simplex_debug.o 
	$(CC) -o algo_test_debug.out algo_test_debug.o vertex_debug.o downhill_simplex_debug.o -g -lm

debug_algo_test2: algo_test2_debug.o vertex_debug.o downhill_simplex_debug.o 
	$(CC) -o algo_test2_debug.out algo_test_debug.o vertex_debug.o downhill_simplex_debug.o -g -lm

demo_mlp_debug.o: demo_mlp.c demo_mlp.h vertex.h downhill_simplex.h
	$(CC) -c demo_mlp.c -o demo_mlp_debug.o -g

algo_test_debug.o: algo_test.c vertex.h
	$(CC) -c algo_test.c -o algo_test_debug.o -g

algo_test2_debug.o: algo_test2.c vertex.h
	$(CC) -c algo_test2.c -o algo_test_debug.o -g	
	
vertex_debug.o: vertex.c vertex.h
	$(CC) -c vertex.c -o vertex_debug.o -g
	
downhill_simplex_debug.o: downhill_simplex.c downhill_simplex.h vertex.h
	$(CC) -c downhill_simplex.c -o downhill_simplex_debug.o -g

# ============================================
# Clean
# ============================================
clean:
	rm -f *.o
