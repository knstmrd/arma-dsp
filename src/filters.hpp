#ifndef arma_dsp_filters_hpp
#define arma_dsp_filters_hpp

#include <armadillo>
#include <cmath>
#include "windows.hpp"
#include "filters.hpp"

void fir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, arma::vec &output);

void iir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, const arma::vec &fb_coeffs, arma::vec &output);

arma::vec fir_filter(const arma::vec &signal, const arma::vec &ff_coeffs);

arma::vec iir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, const arma::vec &fb_coeffs);

arma::vec one_zero_filter(const arma::vec &signal, double ff_coeff);

arma::vec one_pole_filter(const arma::vec &signal, double fb_coeff);

arma::vec two_pole_resonator(const arma::vec &signal, double frequency, double damping);

#endif