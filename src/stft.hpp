#ifndef arma_dsp_stft
#define arma_dsp_stft

#include <armadillo>
#include <functional>

arma::cx_mat stft(const arma::vec &signal, const arma::vec &window_array, int framelength=1024, int overlap=2, bool centered=true, bool half=true);

arma::cx_mat stft(const arma::vec &signal, std::function<arma::vec(unsigned int)> window, int framelength=1024, int overlap=2, bool centered=true, bool half=true);

arma::cx_mat stft(const arma::vec &signal, int framelength=1024, int overlap=2, bool centered=true, bool half=true);

#endif