/**
 * SampleDecoder.h
 *
 * The chromosome's fitness is computed as the sum of its individual alleles. We also show how to
 * generate a random permutation of {0, 1, ..., n-1} using the supplied chromosome.
 *
 * Any Decoder class must implement either of the methods:
 *     1. double decode(std::vector< double >&)
 *     2. double decode(std::vector< double >&) const
 *     3. double decode(const std::vector< double >&)
 *     4. double decode(const std::vector< double >&) const
 * where the returned double corresponds to the fitness of that chromosome. If parallel decoding
 * is to be used in the BRKGA framework, then decode() *must* be thread-safe; the best way to
 * guarantee this is by via member const-correctness -- see (2) and (4) above --  so that the
 * property will be checked at compile time. An exception to this rule is the use of the mutant
 * modifier in data members of the decoder, which bypasses const-correctness and may introduce
 * dangerous race conditions in a multithreaded environment.
 *
 * The chromosome inside the BRKGA framework can be changed if desired. To do so, just use the
 * signatures (1) and (3) above which do not forbid the chromosome to be changed (and such change
 * gets reflected in BRKGA). Please use double values in the interval [0,1) when updating, thus
 * obeying the BRKGA guidelines -- for speed, BRKGA does *not* enforce this.
 *
 * Created on : Nov 17, 2011 by rtoso
 * Authors    : Rodrigo Franco Toso <rtoso@cs.rutgers.edu>
 *              Mauricio G.C. Resende <mgcr@research.att.com>
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018
 * Rodrigo Franco Toso (rfrancotoso@gmail.com) and
 * Mauricio G.C. Resende
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef SAMPLEDECODER_H
#define SAMPLEDECODER_H

#include <list>
#include <vector>
#include <algorithm>

class SampleDecoder {
public:
	SampleDecoder();	// Constructor
	~SampleDecoder();	// Destructor

	// Decode a chromosome, returning its fitness as a double-precision floating point:
	double decode(const std::vector< double >& chromosome) const;

private:
};

#endif
