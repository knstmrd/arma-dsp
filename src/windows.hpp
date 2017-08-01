#ifndef arma_dsp_windows_hpp
#define arma_dsp_windows_hpp

#include <armadillo>
#include <math>

arma::vec window_rectangular(int framelength);
arma::vec window_gaussian(int framelength, double sigma);
arma::vec window_hann(int framelength);
arma::vec window_hamming(int framelength);
arma::vec window_blackman(int framelength, double alpha);

#endif