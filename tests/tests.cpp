#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "max_error.hpp"
#include "../src/arma-dsp.hpp"


TEST_CASE( "Rectangular window function work correctly", "[window]" ) {
    arma::vec a = window_rectangular(3);

    REQUIRE( a.n_elem == 3 );
    REQUIRE( a[0] == 1.0 );
    REQUIRE( a[1] == 1.0 );
    REQUIRE( a[2] == 1.0 );
}

TEST_CASE( "Triangular window function work correctly", "[window]" ) {
    arma::vec a = window_triangle(3);
    arma::vec b = window_triangle(4);

    REQUIRE( a.n_elem == 3 );
    REQUIRE( b.n_elem == 4 );

    REQUIRE( fabs(a[0] - 0.5) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[2] - 0.5) < MAX_ABSOLUTE_ERROR );

    REQUIRE( fabs(b[0] - 0.25) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[1] - 0.75) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[2] - 0.75) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[3] - 0.25) < MAX_ABSOLUTE_ERROR );
}

TEST_CASE( "Gaussian window function work correctly", "[window]" ) {
    arma::vec a = window_gaussian(3, 0.5);
    arma::vec b = window_gaussian(4, 0.5);
    arma::vec c = window_gaussian(3, 0.7);

    REQUIRE( a.n_elem == 3 );
    REQUIRE( b.n_elem == 4 );

    // REQUIRE( fabs(a[0] - 0.5) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(a[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(a[2] - 0.5) < MAX_ABSOLUTE_ERROR );

    // REQUIRE( fabs(b[0] - 0.25) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[1] - 0.75) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[2] - 0.75) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[3] - 0.25) < MAX_ABSOLUTE_ERROR );
}

TEST_CASE( "Hann window function work correctly", "[window]" ) {
    arma::vec a = window_hann(3);
    arma::vec b = window_hann(4);

    REQUIRE( a.n_elem == 3 );
    REQUIRE( b.n_elem == 4 );

    // REQUIRE( fabs(a[0] - 0.5) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(a[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(a[2] - 0.5) < MAX_ABSOLUTE_ERROR );

    // REQUIRE( fabs(b[0] - 0.25) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[1] - 0.75) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[2] - 0.75) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[3] - 0.25) < MAX_ABSOLUTE_ERROR );
}

TEST_CASE( "Hamming window function work correctly", "[window]" ) {
    arma::vec a = window_hamming(3);
    arma::vec b = window_hamming(4);

    REQUIRE( a.n_elem == 3 );
    REQUIRE( b.n_elem == 4 );

    // REQUIRE( fabs(a[0] - 0.5) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(a[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(a[2] - 0.5) < MAX_ABSOLUTE_ERROR );

    // REQUIRE( fabs(b[0] - 0.25) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[1] - 0.75) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[2] - 0.75) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[3] - 0.25) < MAX_ABSOLUTE_ERROR );
}

TEST_CASE( "Blackman window function work correctly", "[window]" ) {
    arma::vec a = window_blackman(3);
    arma::vec b = window_blackman(4);
    arma::vec c = window_blackman(3, 0.2);

    REQUIRE( a.n_elem == 3 );
    REQUIRE( b.n_elem == 4 );

    // REQUIRE( fabs(a[0] - 0.5) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(a[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(a[2] - 0.5) < MAX_ABSOLUTE_ERROR );

    // REQUIRE( fabs(b[0] - 0.25) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[1] - 0.75) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[2] - 0.75) < MAX_ABSOLUTE_ERROR );
    // REQUIRE( fabs(b[3] - 0.25) < MAX_ABSOLUTE_ERROR );
}