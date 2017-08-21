#include "stft.hpp"
#include <cmath>
#include "windows.hpp"
#include "helpers.hpp"

arma::cx_mat stft(const arma::vec &signal, const arma::vec &window_array, int framelength, int overlap, bool centered, bool half) {
    arma::vec data;

    
    if (centered) {
        data = pad_zeros(signal, framelength / 2, true);
        data = pad_zeros(data, framelength / 2, false);
    }
    else {
        data = signal;
    }
    int offset = framelength / overlap;
    data = pad_zeros(data, ceil(data.n_elem / framelength) * framelength - data.n_elem, true);
    arma::cx_vec fft_out = arma::fft(data.subvec(0, framelength-1) % window_array) / (framelength / offset / 2);
    
    if (half) {
        fft_out = fft_out.subvec(0, fft_out.n_elem / 2);
    }
    arma::cx_rowvec r_fft_out(fft_out.n_elem);
    unsigned int i, j=1, k;
    for (i=0; i<r_fft_out.n_elem; i++) {
        r_fft_out[i] = fft_out[i];
    }

    arma::cx_mat output = arma::zeros<arma::cx_mat>((data.n_elem - framelength + offset) / offset,fft_out.n_elem);
    
    output.row(0) = r_fft_out;
    for (i=offset; i<data.n_elem - framelength + offset; i+=offset) {
        fft_out = arma::fft(data.subvec(i, i+framelength-1) % window_array) / (framelength / offset / 2);

        if (half) {
            fft_out = fft_out.subvec(0, fft_out.n_elem / 2);
        }
        for (k=0; k<r_fft_out.n_elem; k++) {
            r_fft_out[k] = fft_out[k];
        }
        output.row(j) = r_fft_out;
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