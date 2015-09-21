BRKGA for the travelling salesman problem: a simple algorithm to the symmetric TSP.

To recompile and run the program, type:
	cd ./examples/brkga-tsp
	make clean
	make
	./brkga-tsp tsplib/brd14051.tsp

The problem instance is specified on the command line (brd14051.tsp) and follows the TSPLib format,
see http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/

Parameters are defined in brkga-tsp.cpp; to modify, edit file brkga-tsp.cpp, change the desired
parameter value at the top of the file and recompile the program as shown above.
