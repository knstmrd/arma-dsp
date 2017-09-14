#ifndef arma_dsp_windows_hpp
#define arma_dsp_windows_hpp

#include <armadillo>
#include <cmath>

namespace adsp {
    arma::vec window_rectangular(unsigned int framelength);
    arma::vec window_triangle(unsigned int framelength);
    arma::vec window_welch(unsigned int framelength);
    arma::vec window_gaussian(unsigned int framelength, double sigma);
    arma::vec window_hann(unsigned int framelength);
    arma::vec window_hamming(unsigned int framelength);
    arma::vec window_blackman(unsigned int framelength, double alpha=0.16);
} // adsp

#endif