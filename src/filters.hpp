#ifndef arma_dsp_filters_hpp
#define arma_dsp_filters_hpp

#include <armadillo>
#include <cmath>
#include "windows.hpp"
#include "filters.hpp"

void fir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, arma::vec &output);

arma::vec fir_filter(const arma::vec &signal, const arma::vec &ff_coeffs);

void iir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, const arma::vec &fb_coeffs, arma::vec &output);

arma::vec iir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, const arma::vec &fb_coeffs);

void one_zero_filter(const arma::vec &signal, double ff_coeff, arma::vec &output);

arma::vec one_zero_filter(const arma::vec &signal, double ff_coeff);

void one_pole_filter(const arma::vec &signal, double ff_coeff, double fb_coeff, arma::vec &output);

arma::vec one_pole_filter(const arma::vec &signal, double ff_coeff, double fb_coeff);

void two_pole_resonator(const arma::vec &signal, double frequency, double damping, arma::vec &output);

arma::vec two_pole_resonator(const arma::vec &signal, double frequency, double damping);

#endif