#ifndef arma_dsp_filters_hpp
#define arma_dsp_filters_hpp

#include <armadillo>
#include <cmath>
#include "windows.hpp"
#include "filters.hpp"

arma::vec filter(arma::vec signal, arma::vec ff_coeffs, arma::vec fb_coeffs);

arma::vec fir_filter(arma::vec signal, arma::vec ff_coeffs);

arma::vec iir_filter(arma::vec signal, arma::vec fb_coeffs);

arma::vec one_zero_filter(arma::vec signal, double ff_coeff);

arma::vec one_pole_filter(arma::vec signal, double fb_coeff);

arma::vec two_pole_resonator(arma::vec signal, double frequency, double damping);

#endif