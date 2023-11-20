CC ?= gcc

all: algo_test

# ============================================
# Compile and Build
# ============================================
algo_test: algo_test.o vertex.o 
	$(CC) -o algo_test algo_test.o vertex.o 

algo_test.o: algo_test.c vertex.h
	$(CC) -c algo_test.c
	
vertex.o: vertex.c vertex.h
	$(CC) -c vertex.c 


# ============================================
# Debug: compile with the -g tag
# ============================================
debug: algo_test_debug.o vertex_debug.o 
	$(CC) -o algo_test_debug algo_test.o vertex.o -g

algo_test_debug.o: algo_test.c vertex.h
	$(CC) -c algo_test.c -g
	
vertex_debug.o: vertex.c vertex.h
	$(CC) -c vertex.c -g

# ============================================
# Clean
# ============================================
clean:
	rm -f *.o
