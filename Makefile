CC ?= gcc

all: algo_test

# ============================================
# Compile and Build
# ============================================
algo_test: algo_test.o vertex.o downhill_simplex.o
	$(CC) -o algo_test.out algo_test.o vertex.o downhill_simplex.o -lm

algo_test.o: algo_test.c vertex.h downhill_simplex.h
	$(CC) -c algo_test.c
	
vertex.o: vertex.c vertex.h
	$(CC) -c vertex.c 
	
downhill_simplex.o: downhill_simplex.c downhill_simplex.h vertex.h
	$(CC) -c downhill_simplex.c 	


# ============================================
# Debug: compile with the -g tag
# ============================================
debug: algo_test_debug.o vertex_debug.o downhill_simplex_debug.o 
	$(CC) -o algo_test_debug.out algo_test_debug.o vertex_debug.o downhill_simplex_debug.o -g -lm

algo_test_debug.o: algo_test.c vertex.h
	$(CC) -c algo_test.c -o algo_test_debug.o -g
	
vertex_debug.o: vertex.c vertex.h
	$(CC) -c vertex.c -o vertex_debug.o -g
	
downhill_simplex_debug.o: downhill_simplex.c downhill_simplex.h vertex.h
	$(CC) -c downhill_simplex.c -o downhill_simplex_debug.o -g

# ============================================
# Clean
# ============================================
clean:
	rm -f *.o
