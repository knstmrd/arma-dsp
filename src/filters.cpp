#include "filters.hpp"
#include "helpers.hpp"
#include <iostream>

void fir_filter(const arma::vec &signal, const arma::vec &reverse_ff_coeffs, arma::vec &output) {
    int i;
    for (i=0; i<reverse_ff_coeffs.n_elem; i++) {
        output[i] = arma::dot(signal.subvec(0, i), reverse_ff_coeffs.subvec(reverse_ff_coeffs.n_elem-1-i, reverse_ff_coeffs.n_elem-1));
    }

    for (i=reverse_ff_coeffs.n_elem; i<signal.n_elem; i++) {
        output[i] = arma::dot(signal.subvec(i + 1 - reverse_ff_coeffs.n_elem, i), reverse_ff_coeffs);
    }
}

void fir_filter(const arma::vec &signal, double input_gain, double ff_coeff, unsigned int delay, arma::vec &output) {
    output.subvec(0, delay-1) = input_gain * signal.subvec(0, delay-1);
    output.subvec(delay, signal.n_elem-1) = input_gain * signal.subvec(delay, signal.n_elem-1) + ff_coeff * signal.subvec(0, signal.n_elem - delay - 1);
}

arma::vec fir_filter(const arma::vec &signal, const arma::vec &ff_coeffs) {
    arma::vec output(signal.n_elem);

    fir_filter(signal, reverse_copy(ff_coeffs), output);
    return output;
}

arma::vec fir_filter(const arma::vec &signal, double input_gain, double ff_coeff, unsigned int delay) {
    arma::vec output(signal.n_elem);

    fir_filter(signal, input_gain, ff_coeff, delay, output);
    return output;
}

void iir_filter(const arma::vec &signal, const arma::vec &reverse_ff_coeffs, const arma::vec &reverse_fb_coeffs, arma::vec &output) {
    output = fir_filter(signal, reverse_ff_coeffs);

    int i;

    for (i=1; i<=reverse_fb_coeffs.n_elem; i++) {
        output[i] -= arma::dot(output.subvec(0, i-1), reverse_fb_coeffs.subvec(0, i-1));
    }

    for (i=reverse_fb_coeffs.n_elem+1; i<=signal.n_elem; i++) {
        output[i] -= arma::dot(signal.subvec(i - signal.n_elem + 1, i-1), reverse_fb_coeffs);
    }
}

void iir_filter(const arma::vec &signal, double input_gain, double ff_coeff, unsigned int ff_delay, double fb_coeff, unsigned int fb_delay, arma::vec &output) {
    fir_filter(signal, input_gain, ff_coeff, ff_delay, output);

    for (int i=fb_delay; i<signal.n_elem; i++) {
        output[i] -= fb_coeff * output[i - fb_delay];
    }
}
// y[n] = input_gain * x[n] + ff_coeff * x[n - ff_delay] - fb_coeff * y[n - fb_delay]

arma::vec iir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, const arma::vec &fb_coeffs) {
    arma::vec output(signal.n_elem);

    iir_filter(signal, reverse_copy(ff_coeffs), reverse_copy(fb_coeffs), output);
    return output;
}

arma::vec iir_filter(const arma::vec &signal, double input_gain, double ff_coeff, unsigned int ff_delay, double fb_coeff, unsigned int fb_delay) {
    arma::vec output(signal.n_elem);

    iir_filter(signal, input_gain, ff_coeff, ff_delay, fb_coeff, fb_delay, output);
    return output;
}

void one_zero_filter(const arma::vec &signal, double input_gain, double ff_coeff, arma::vec &output) {
    fir_filter(signal, input_gain, ff_coeff, 1, output);
}

arma::vec one_zero_filter(const arma::vec &signal, double input_gain, double ff_coeff) {
    arma::vec output(signal.n_elem);

    fir_filter(signal, input_gain, ff_coeff, 1, output);
    return output;
}

void one_pole_filter(const arma::vec &signal, double input_gain, double fb_coeff, arma::vec &output) {
    iir_filter(signal, input_gain, 0.0, 0, fb_coeff, 1, output);
}

arma::vec one_pole_filter(const arma::vec &signal, double input_gain, double fb_coeff) {
    arma::vec output(signal.n_elem);

    one_pole_filter(signal, input_gain, fb_coeff, output);
    return output;
}

void allpass_filter(const arma::vec &signal, double gain, unsigned int delay, arma::vec &output) {
    iir_filter(signal, -gain, 1., delay, -gain, delay, output);
}

arma::vec allpass_filter(const arma::vec &signal, double gain, unsigned int delay) {
    arma::vec output(signal.n_elem);

    allpass_filter(signal, gain, delay, output);
    return output;
}

void lowpass_filter(const arma::vec &signal, unsigned int sampling_rate, double cutoff_frequency, arma::vec &output) {
    double alpha = 2.0 * M_PI * cutoff_frequency / (sampling_rate * (2.0 * M_PI * cutoff_frequency / sampling_rate + 1.0));
    iir_filter(signal, alpha, 0.0, 0, -(1 - alpha), 1, output);
}

arma::vec lowpass_filter(const arma::vec &signal, unsigned int sampling_rate, double cutoff_frequency) {
    arma::vec output(signal.n_elem);

    allpass_filter(signal, sampling_rate, cutoff_frequency, output);
    return output;
}