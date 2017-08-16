#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "max_error.hpp"
#include "../src/arma-dsp.hpp"


TEST_CASE( "Zero padding function working correctly", "[helper]") {
    arma::vec a = arma::ones(1);

    arma::vec b = pad_zeros(a, 1);
    arma::vec c = pad_zeros(a, 1, false);

    REQUIRE( b.n_elem == 2 );
    REQUIRE( c.n_elem == 2 );
    REQUIRE( fabs(b[0] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[1] - 0.0) < MAX_ABSOLUTE_ERROR );

    REQUIRE( fabs(c[0] - 0.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(c[1] - 1.0) < MAX_ABSOLUTE_ERROR );
}

TEST_CASE( "Rectangular window function work correctly", "[window]" ) {
    arma::vec a = window_rectangular(3);

    REQUIRE( a.n_elem == 3 );
    REQUIRE( fabs(a[0] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[2] - 1.0) < MAX_ABSOLUTE_ERROR );
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

    REQUIRE( fabs(a[0] - 0.13533528) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[2] - 0.13533528) < MAX_ABSOLUTE_ERROR );

    REQUIRE( fabs(b[0] - 0.011109) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[1] - 0.60653066) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[2] - 0.60653066) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[3] - 0.011109) < MAX_ABSOLUTE_ERROR );

    REQUIRE( fabs(c[0] - 0.36044779) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(c[1] - 1.) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(c[2] - 0.36044779) < MAX_ABSOLUTE_ERROR );
}

TEST_CASE( "Hann window function work correctly", "[window]" ) {
    arma::vec a = window_hann(3);
    arma::vec b = window_hann(4);

    REQUIRE( a.n_elem == 3 );
    REQUIRE( b.n_elem == 4 );

    REQUIRE( fabs(a[0] - 0.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[2] - 0.0) < MAX_ABSOLUTE_ERROR );

    REQUIRE( fabs(b[0] - 0.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[1] - 0.75) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[2] - 0.75) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[3] - 0.0) < MAX_ABSOLUTE_ERROR );
}

TEST_CASE( "Hamming window function work correctly", "[window]" ) {
    arma::vec a = window_hamming(3);
    arma::vec b = window_hamming(4);

    REQUIRE( a.n_elem == 3 );
    REQUIRE( b.n_elem == 4 );

    REQUIRE( fabs(a[0] - 0.08) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[2] - 0.08) < MAX_ABSOLUTE_ERROR );

    REQUIRE( fabs(b[0] - 0.08) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[1] - 0.77) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[2] - 0.77) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[3] - 0.08) < MAX_ABSOLUTE_ERROR );
}

TEST_CASE( "Blackman window function work correctly", "[window]" ) {
    arma::vec a = window_blackman(3);
    arma::vec b = window_blackman(4);

    REQUIRE( a.n_elem == 3 );
    REQUIRE( b.n_elem == 4 );

    REQUIRE( fabs(a[0] - 0.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(a[2] - 0.0) < MAX_ABSOLUTE_ERROR );

    REQUIRE( fabs(b[0] - 0.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[1] - 0.63) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[2] - 0.63) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(b[3] - 0.0) < MAX_ABSOLUTE_ERROR );
}

TEST_CASE( "FIR filter working", "[filter][fir]" ) {
    arma::vec signal = {2., 1., 0., 0.};
    arma::vec coeffs_1 = {1.}; // this leaves the signal unchanged
    arma::vec coeffs_2 = {1., 0.5}; 
    arma::vec coeffs_3 = {1., 0.5, 0.25}; 

    arma::vec output_1 = fir_filter(signal, coeffs_1);
    REQUIRE( fabs(output_1[0] - 2.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_1[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_1[2] - 0.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_1[3] - 0.0) < MAX_ABSOLUTE_ERROR );

    arma::vec output_2 = fir_filter(signal, coeffs_2);
    REQUIRE( fabs(output_2[0] - 2.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_2[1] - 2.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_2[2] - 0.5) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_2[3] - 0.0) < MAX_ABSOLUTE_ERROR );

    arma::vec output_3 = fir_filter(signal, coeffs_3);
    REQUIRE( fabs(output_3[0] - 2.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_3[1] - 2.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_3[2] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_3[3] - 0.25) < MAX_ABSOLUTE_ERROR );

}

// fir_filter(const arma::vec &signal, double input_gain, double ff_coeff, unsigned int delay)


// iir_filter(const arma::vec &signal, double input_gain, double ff_coeff, int ff_delay, double fb_coeff, unsigned int fb_delay)

TEST_CASE( "IIR filter working", "[filter][iir]" ) {
    arma::vec signal = {2., 1., 0., 0.};
    arma::vec ff_coeffs_1 = {1.};
    arma::vec fb_coeffs_1 = {1}; 

    arma::vec ff_coeffs_2 = {1., -1}; 
    arma::vec fb_coeffs_2 = {-1, 1}; 

    arma::vec ff_coeffs_3 = {1., -1, 2.}; 
    arma::vec fb_coeffs_3 = {-1, 1, -1.}; 

    arma::vec output_1 = iir_filter(signal, ff_coeffs_1, fb_coeffs_1);
    REQUIRE( fabs(output_1[0] - 2.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_1[1] - -1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_1[2] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_1[3] - -1.0) < MAX_ABSOLUTE_ERROR );

    arma::vec output_2 = iir_filter(signal, ff_coeffs_2, fb_coeffs_2);
    REQUIRE( fabs(output_2[0] - 2.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_2[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_2[2] - -2.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_2[3] - -3.0) < MAX_ABSOLUTE_ERROR );

    arma::vec output_3 = iir_filter(signal, ff_coeffs_3, fb_coeffs_3);
    REQUIRE( fabs(output_3[0] - 2.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_3[1] - 1.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_3[2] - 2.0) < MAX_ABSOLUTE_ERROR );
    REQUIRE( fabs(output_3[3] - 5.0) < MAX_ABSOLUTE_ERROR );

}