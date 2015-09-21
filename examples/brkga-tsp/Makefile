# Compiler binary:
CPP= g++

# Recommended compiler flags for speed:
#	OpenMP enabled
#	full binary code optimization
#	full error and warning reports
#	no range checking within BRKGA:
CFLAGS= -O3 -fopenmp -Wextra -Wall -Weffc++ -ansi -pedantic -Woverloaded-virtual -Wcast-align -Wpointer-arith

# Compiler flags for debugging; uncomment if needed:
#	range checking enabled in the BRKGA API
#	OpenMP disabled
#	no binary code optimization
#CFLAGS= -DRANGECHECK -Wextra -Wall -Weffc++ -ansi -pedantic -Woverloaded-virtual -Wcast-align -Wpointer-arith

OBJECTS= TSPInstance.o TSPSolver.o TSPDecoder.o Population.o brkga-tsp.o

# Targets:
all: brkga-tsp

brkga-tsp: $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o brkga-tsp

brkga-tsp.o:
	$(CPP) $(CFLAGS) -c brkga-tsp.cpp

TSPInstance.o:
	$(CPP) $(CFLAGS) -c TSPInstance.cpp

TSPSolver.o:
	$(CPP) $(CFLAGS) -c TSPSolver.cpp

TSPDecoder.o:
	$(CPP) $(CFLAGS) -c TSPDecoder.cpp

Population.o:
	$(CPP) $(CFLAGS) -c brkgaAPI/Population.cpp

# Remove:
clean:
	rm -f brkga-stp $(OBJECTS)
