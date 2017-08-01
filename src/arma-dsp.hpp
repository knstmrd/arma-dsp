#ifndef arma_dsp_hpp
#define arma_dsp_hpp

#include <armadillo>
#include <math>
#include <function>
#include "windows.hpp"

arma::vec filter(arma::vec signal, arma::vec ff_coeffs, arma::vec fb_coeffs);

arma::vec one_zero_filter(arma::vec signal, double ff_coeff);

arma::vec one_pole_filter(arma::vec signal, double fb_coeff);

arma::vec two_pole_resonator(arma::vec signal, double frequency, double damping);

cx_mat stft(arma::vec signal, arma::vec window_array, int framelength=1024, int overlap=2, bool half=true);

cx_mat stft(arma::vec signal, std::function<arma::vec(int)> window, int framelength=1024, int overlap=2, bool half=true);

cx_mat stft(arma::vec signal, std::function<arma::vec(int, double)> window, int framelength=1024, int overlap=2, bool half=true);

#endif