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

# Objects:
OBJECTS= Node.o SetCoveringDecoder.o SetCoveringSolution.o Population.o brkga-scp.o

# Targets:
all: brkga-scp

brkga-scp: $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o brkga-scp

brkga-scp.o:
	$(CPP) $(CFLAGS) -c brkga-scp.cpp

Node.o:
	$(CPP) $(CFLAGS) -c Node.cpp

SetCoveringDecoder.o:
	$(CPP) $(CFLAGS) -c SetCoveringDecoder.cpp

SetCoveringSolution.o:
	$(CPP) $(CFLAGS) -c SetCoveringSolution.cpp

Population.o:
	$(CPP) $(CFLAGS) -c brkgaAPI/Population.cpp

clean:
	rm -f api-usage $(OBJECTS)
