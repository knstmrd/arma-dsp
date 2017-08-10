# arma-dsp

A C++ DSP library using the [Armadillo](http://arma.sourceforge.net/) linear algebra library.

# Installation

## Running tests

To run the included tests (using an included copy of the [Catch](https://github.com/philsquared/Catch) test framework), run `make test`. Since some of the tests involve comparisons of floating point numbers, approximate equality is considered; the maximum absolute error that is allowed is set in the `tests/max_error.hpp` file. The created executable can be run with various command-line options (see Catch documentation).

Mozilla Public License 2.0