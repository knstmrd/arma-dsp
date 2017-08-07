#ifndef arma_dsp_filters_hpp
#define arma_dsp_filters_hpp

#include <armadillo>
#include <cmath>
#include "windows.hpp"
#include "filters.hpp"

void fir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, arma::vec &output);

void fir_filter(const arma::vec &signal, double ff_coeff, int delay, arma::vec &output);

void fir_filter(const arma::vec &signal, double input_gain, double ff_coeff, int delay, arma::vec &output);

arma::vec fir_filter(const arma::vec &signal, const arma::vec &ff_coeffs);

arma::vec fir_filter(const arma::vec &signal, double ff_coeff, int delay);
// y[n] = ff_coeff * x[n - delay]

arma::vec fir_filter(const arma::vec &signal, double input_gain, double ff_coeff, int delay);
// y[n] = input_gain * x[n] + ff_coeff * x[n - delay]

void iir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, const arma::vec &fb_coeffs, arma::vec &output);

void iir_filter(const arma::vec &signal, double ff_coeff, int ff_delay, double fb_coeff, int fb_delay, arma::vec &output);

void iir_filter(const arma::vec &signal, double input_gain, double ff_coeff, int ff_delay, double fb_coeff, int fb_delay, arma::vec &output);

arma::vec iir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, const arma::vec &fb_coeffs);

arma::vec iir_filter(const arma::vec &signal, double ff_coeff, int ff_delay, double fb_coeff, int fb_delay);
// y[n] = ff_coeff * x[n - ff_delay] - fb_coeff * y[n - fb_delay]

arma::vec iir_filter(const arma::vec &signal, double input_gain, double ff_coeff, int ff_delay, double fb_coeff, int fb_delay);
// y[n] = input_gain * x[n] + ff_coeff * x[n - ff_delay] - fb_coeff * y[n - fb_delay]

void one_zero_filter(const arma::vec &signal, double ff_coeff, arma::vec &output);

arma::vec one_zero_filter(const arma::vec &signal, double ff_coeff);

void one_pole_filter(const arma::vec &signal, double ff_coeff, double fb_coeff, arma::vec &output);

arma::vec one_pole_filter(const arma::vec &signal, double ff_coeff, double fb_coeff);

void two_pole_resonator(const arma::vec &signal, double frequency, double damping, arma::vec &output);

arma::vec two_pole_resonator(const arma::vec &signal, double frequency, double damping);

#endif