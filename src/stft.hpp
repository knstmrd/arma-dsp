#ifndef arma_dsp_stft
#define arma_dsp_stft

#include <armadillo>
#include <functional>

namespace adsp {
    arma::cx_mat stft(const arma::vec &signal, const arma::vec &window_array, unsigned int framelength=1024, unsigned int overlap=2, bool centered=true, bool half=true);

    arma::cx_mat stft(const arma::vec &signal, std::function<arma::vec(unsigned int)> window, unsigned int framelength=1024, unsigned int overlap=2, bool centered=true, bool half=true);

    arma::cx_mat stft(const arma::vec &signal, unsigned int framelength=1024, unsigned int overlap=2, bool centered=true, bool half=true);

    arma::vec istft(const arma::cx_mat &spectrogram, const arma::vec &window_array, unsigned int framelength=1024, unsigned int overlap=2, bool centered=true, bool half=true);

    arma::vec istft(const arma::cx_mat &spectrogram, std::function<arma::vec(unsigned int)> window, unsigned int framelength=1024, unsigned int overlap=2, bool centered=true, bool half=true);

    arma::vec istft(const arma::cx_mat &spectrogram, unsigned int framelength=1024, unsigned int overlap=2, bool centered=true, bool half=true);
} // adsp

#endif