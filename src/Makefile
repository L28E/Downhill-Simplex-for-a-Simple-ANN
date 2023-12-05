CC ?= gcc

all: mlp_demo algo_demo simple_mlp_demo

# ============================================
# Compile and build  
# ============================================
simple_mlp_demo: simple_mlp_demo.o vertex.o downhill_simplex.o
	$(CC) -o simple_mlp_demo.out simple_mlp_demo.o vertex.o downhill_simplex.o -lm

mlp_demo: mlp_demo.o vertex.o downhill_simplex.o
	$(CC) -o mlp_demo.out mlp_demo.o vertex.o downhill_simplex.o -lm

algo_demo: algo_demo.o vertex.o downhill_simplex.o
	$(CC) -o algo_demo.out algo_demo.o vertex.o downhill_simplex.o -lm

# ---------------------------------------------

simple_mlp_demo.o: simple_mlp_demo.c mlp_demo.h vertex.h downhill_simplex.h
	$(CC) -c simple_mlp_demo.c

mlp_demo.o: mlp_demo.c mlp_demo.h vertex.h downhill_simplex.h
	$(CC) -c mlp_demo.c

algo_demo.o: algo_demo.c vertex.h downhill_simplex.h
	$(CC) -c algo_demo.c

vertex.o: vertex.c vertex.h
	$(CC) -c vertex.c 
	
downhill_simplex.o: downhill_simplex.c downhill_simplex.h vertex.h
	$(CC) -c downhill_simplex.c 	

# ============================================
# Debug: compile and build with the -g tag
# ============================================
debug_mlp_demo: mlp_demo_debug.o vertex_debug.o downhill_simplex_debug.o
	$(CC) -o mlp_demo_debug.out mlp_demo_debug.o vertex_debug.o downhill_simplex_debug.o -g -lm

debug_algo_demo: algo_demo_debug.o vertex_debug.o downhill_simplex_debug.o 
	$(CC) -o algo_demo_debug.out algo_demo_debug.o vertex_debug.o downhill_simplex_debug.o -g -lm

# ---------------------------------------------

mlp_demo_debug.o: mlp_demo.c mlp_demo.h vertex.h downhill_simplex.h
	$(CC) -c mlp_demo.c -o mlp_demo_debug.o -g

algo_demo_debug.o: algo_demo.c vertex.h
	$(CC) -c algo_demo.c -o algo_demo_debug.o -g

vertex_debug.o: vertex.c vertex.h
	$(CC) -c vertex.c -o vertex_debug.o -g
	
downhill_simplex_debug.o: downhill_simplex.c downhill_simplex.h vertex.h
	$(CC) -c downhill_simplex.c -o downhill_simplex_debug.o -g

# ============================================
# Clean
# ============================================
clean:
	rm -f *.o
