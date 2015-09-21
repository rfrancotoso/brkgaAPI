            The BRKGA API documentation
            by Rodrigo Toso and Mauricio Resende
            rtoso@cs.rutgers.edu and mgcr@research.att.com

1) Algorithm implementation: the standalone API is located under the directory brkgaAPI.

2) Third party supporting code: under brkgaAPI/MTRand.h we include the class MTRand, a third party
Mersenne-Twister pseudo-random number generator that was slightly modified to work with the BRKGA
class. Authorship and licensing terms, together with the modifications we have introduced, are
included in the class implementation.

3) Documentation: please see the accompanying paper.

4) Examples
4.1) Plain driver: a sample driver and Decoder class that make use of the BRKGA API are provided
in the directory examples/api-usage. Documentation regarding the driver is in the source file
api-usage.cpp. To compile it, just type in "make" inside the directory.

4.2) BRKGA for the travelling salesman problem: we have implemented a simple algorithm to the
symmetric TSP. To compile it, just type in "make" inside the directory. To use it, type in the
binary name followed by the path to an instance file. Two instances are included under
directory tsplib.

4.3) BRKGA for the set covering problem: this implementation is more complex as it makes use of
local search heuristics in order to improve a solution extracted from the chromosome. Although we
are not very proud about a couple of design choices, the implementation is excellent w.r.t. finding
good solutions even when compared to state-of-the-art algorithms to this problem.

5) Command file: Makefiles are provided with both the example driver and test material.

6) Portability: the code was compiled with the GNU g++ compiler using the following verification
flags: -Wextra -Wall -Weffc++ -ansi -pedantic -Woverloaded-virtual -Wcast-align -Wpointer-arith

7) Machine-dependent code: no machine-dependent code is employed in the API or drivers.

8) Code documentation: our code is systematically documented.