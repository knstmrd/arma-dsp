#ifndef arma_dsp_hpp
#define arma_dsp_hpp

#include <armadillo>
#include <cmath>
#include <function>
#include "windows.hpp"
#include "filters.hpp"

cx_mat stft(arma::vec signal, arma::vec window_array, int framelength=1024, int overlap=2, bool half=true);

cx_mat stft(arma::vec signal, std::function<arma::vec(int)> window, int framelength=1024, int overlap=2, bool half=true);

cx_mat stft(arma::vec signal, std::function<arma::vec(int, double)> window, int framelength=1024, int overlap=2, bool half=true);

#endif