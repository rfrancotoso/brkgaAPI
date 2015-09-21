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
OBJECTS= Population.o SampleDecoder.o api-usage.o

# Targets:
all: api-usage

api-usage: $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o api-usage

api-usage.o:
	$(CPP) $(CFLAGS) -c api-usage.cpp

SampleDecoder.o:
	$(CPP) $(CFLAGS) -c SampleDecoder.cpp

Population.o:
	$(CPP) $(CFLAGS) -c brkgaAPI/Population.cpp

clean:
	rm -f api-usage $(OBJECTS)
