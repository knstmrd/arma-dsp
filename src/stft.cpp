#include "stft.hpp"
#include <cmath>
#include "windows.hpp"
#include "helpers.hpp"

arma::cx_mat adsp::stft(const arma::vec &signal, const arma::vec &window_array, unsigned int framelength, unsigned int overlap, bool centered, bool half) {
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

arma::cx_mat adsp::stft(const arma::vec &signal, std::function<arma::vec(unsigned int)> window, unsigned int framelength, unsigned int overlap, bool centered, bool half) {
    arma::vec window_array = window(framelength);
    return stft(signal, window_array, framelength, overlap, centered, half);
}

arma::cx_mat adsp::stft(const arma::vec &signal, unsigned int framelength, unsigned int overlap, bool centered, bool half) {
    return stft(signal, window_welch(framelength), framelength, overlap, centered, half);
}

arma::vec adsp::istft(const arma::cx_mat &spectrogram, const arma::vec &window_array, unsigned int framelength, unsigned int overlap, bool centered, bool half) {
    int offset = framelength / overlap;
    arma::rowvec rwa = arma::conv_to<arma::rowvec>::from(window_array);
    arma::rowvec output = arma::zeros<arma::rowvec>(framelength + (spectrogram.n_rows - 1) * offset);
    arma::cx_rowvec slice = arma::zeros<arma::cx_rowvec>(spectrogram.n_cols * 2 - 2);
    arma::mat ifft_out;
    unsigned int i, j=0, conj_pos;
    
    for (i=0; i<=output.n_elem-framelength; i+=offset) {
        slice.subvec(0, spectrogram.n_cols - 1) = spectrogram.row(j);
        if (half) {
            slice.subvec(spectrogram.n_cols, spectrogram.n_cols * 2 - 3) = reverse_copy(spectrogram.row(j)).subvec(1, spectrogram.n_cols - 2);
            conj_pos = slice.n_elem / 2 + 1;
            slice.subvec(conj_pos, slice.n_elem-1) = arma::conj(slice.subvec(conj_pos, slice.n_elem-1));
        }
        ifft_out = arma::real(ifft(slice));
        output.subvec(i, i+framelength-1) += ifft_out % rwa;
        j++;
    }
    if (centered) {
        output = output.subvec(framelength / 2, output.n_elem - framelength / 2 - 1);
    }

    return arma::conv_to<arma::vec>::from(output);
}

arma::vec adsp::istft(const arma::cx_mat &spectrogram, std::function<arma::vec(unsigned int)> window, unsigned int framelength, unsigned int overlap, bool centered, bool half) {
    arma::vec window_array = window(framelength);
    return istft(spectrogram, window_array, framelength, overlap, centered, half);
}

arma::vec adsp::istft(const arma::cx_mat &spectrogram, unsigned int framelength, unsigned int overlap, bool centered, bool half) {
    return istft(spectrogram, window_welch(framelength), framelength, overlap, centered, half);
}