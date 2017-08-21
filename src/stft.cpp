#include "stft.hpp"
#include <cmath>
#include "windows.hpp"
#include "helpers.hpp"

arma::cx_mat stft(const arma::vec &signal, const arma::vec &window_array, int framelength, int overlap, bool centered, bool half) {
    int outlength = signal.n_elem;
    arma::vec data;

    int offset = framelength / overlap;

    if (centered) {
        data = pad_zeros(data, framelength / 2, true);
        data = pad_zeros(data, framelength / 2, false);
    }
    else {
        data = signal;
    }
    data = pad_zeros(data, ceil(data.n_elem / framelength) * framelength - data.n_elem, true);
    
    arma::cx_vec fft_out = arma::fft(data.subvec(0, framelength-1) % window_array);

    if(half) {
        fft_out = fft_out.subvec(0, fft_out.n_elem / 2);
    }

    arma::cx_mat output = arma::zeros<arma::cx_mat>((data.n_elem - framelength + offset) / offset,fft_out.n_elem);

    int j=1;
    output.col(0) = fft_out;
    for (int i=offset; i<data.n_elem - framelength + offset; i+=offset) {
        fft_out = arma::fft(data.subvec(i, i+framelength-1) % window_array) / (framelength / offset / 2);

        if(half) {
            fft_out = fft_out.subvec(0, fft_out.n_elem / 2);
        }
        output.col(j) = fft_out;
        j += 1;
    }

    return output;
}

arma::cx_mat stft(arma::vec signal, std::function<arma::vec(int)> window, int framelength, int overlap, bool centered, bool half) {
    arma::vec window_array = window(framelength);
    return stft(signal, window_array, framelength, overlap, centered, half);
}

arma::cx_mat stft(const arma::vec &signal, int framelength, int overlap, bool centered, bool half) {
    return stft(signal, window_welch(framelength), framelength, overlap, centered, half);
}