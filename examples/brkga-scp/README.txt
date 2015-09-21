BRKGA for the set covering problem: this implementation makes use of local search heuristics in
order to improve a solution extracted from the chromosome. Although we are not very proud about a
couple of design choices, the implementation is excellent w.r.t. finding good solutions, even when
compared to state-of-the-art algorithms to this problem.

To recompile and run the program using seed 123456 on problem instance scp41.txt using the stopping
rule 0 to stop after 200 generations, type:
	cd ./examples/brkga-scp
	make clean
	make
	./brkga-scp 123456 0 200 ./instances/orlib/scp41.txt

Additional stopping rules are: 1, to stop after a target objective value is found, and 2, to stop
after a given number of generations has passed without improvement in the best objective value.

To set up the BRKGA parameters, edit file algorithm.conf con contain exactly the following data in
the first 7 lines:

0.20 (percentage of the population labeled elite)
0.15 (percentage of the population introduced at random at each generation, the mutants)
0.80 (when applying cross-over, probability that an allele will be copied from the elite parent)
2 (number of independent populations)
2 (number of threads employed to decode chromosomes in parallel)
10 (frequency at which elite individuals are exchanged between the populations)
2 (number of elite individuals to exchange)

The size of the population is determined by the size of the problem n (number of rows): 10 * n.
