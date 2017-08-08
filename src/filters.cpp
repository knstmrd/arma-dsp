#include "filters.hpp"

void fir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, arma::vec &output) {
    int i;
    for (i=0; i<ff_coeffs.n_elem; i++) {
        output[i] = arma::dot(signal.subvec(i, 0), ff_coeffs.subvec(0, i)); // TODO: Does reversing indices work?
    }

    for (i=ff_coeffs.n_elem; i<signal.n_elem; i++) {
        output[i] = arma::dot(signal.subvec(i, i - signal.n_elem + 1), ff_coeffs); // TODO: Does reversing indices work?
    }
}

void fir_filter(const arma::vec &signal, double input_gain, double ff_coeff, int delay, arma::vec &output) {
    int i;
    output.subvec(0, delay-1) = input_gain * signal.subvec(0, delay-1);
    output.subvec(delay, signal.n_elem-1) = input_gain * signal.subvec(delay, signal.n_elem-1) + ff_coeff * signal.subvec(0, signal.n_elem - delay - 1);
}

arma::vec fir_filter(const arma::vec &signal, const arma::vec &ff_coeffs) {
    arma::vec output(signal.n_elem);

    fir_filter(signal, ff_coeffs, output);
    return output;
}

arma::vec fir_filter(const arma::vec &signal, double input_gain, double ff_coeff, int delay) {
    arma::vec output(signal.n_elem);

    fir_filter(signal, input_gain, ff_coeff, delay, output);
    return output;
}

void iir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, const arma::vec &fb_coeffs, arma::vec &output) {
    output = fir_filter(signal, ff_coeffs);

    int i;

    for (i=1; i<=fb_coeffs.n_elem; i++) {
        output[i] -= arma::dot(output.subvec(i-1, 0), fb_coeffs.subvec(0, i-1));
    }

    for (i=fb_coeffs.n_elem+1; i<=signal.n_elem; i++) {
        output[i] = arma::dot(signal.subvec(i-1, i - signal.n_elem + 1), fb_coeffs);
    }
}

void iir_filter(const arma::vec &signal, double input_gain, double ff_coeff, int ff_delay, double fb_coeff, int fb_delay, arma::vec &output) {
    fir_filter(signal, input_gain, ff_coeff, ff_delay, output);

    for (i=fb_delay, i<signal.n_elem; i++) {
        output[i] -= fb_coeff * output[i - fb_delay];
    }
}
// y[n] = input_gain * x[n] + ff_coeff * x[n - ff_delay] - fb_coeff * y[n - fb_delay]

arma::vec iir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, const arma::vec &fb_coeffs) {
    arma::vec output(signal.n_elem);

    iir_filter(signal, ff_coeffs, fb_coeffs, output);
    return output;
}

arma::vec iir_filter(const arma::vec &signal, double input_gain, double ff_coeff, int ff_delay, double fb_coeff, int fb_delay) {
    arma::vec output(signal.n_elem);

    iir_filter(signal, input_gain, ff_coeff, ff_delay, fb_coeff, fb_delay, output);
    return output;
}

void one_zero_filter(const arma::vec &signal, double ff_coeff, arma::vec &output) {
    arma::vec ffc(1) = {ff_coeff};

    fir_filter(signal, ffc, output);
}

arma::vec one_zero_filter(const arma::vec &signal, double ff_coeff) {
    arma::vec output(signal.n_elem);

    fir_filter(signal, ff_coeff, output);
    return output;
}

void one_pole_filter(const arma::vec &signal, double ff_coeff, double fb_coeff, arma::vec &output) {
    arma::vec ffc(1) = {ff_coeff};
    arma::vec fbc(1) = {fb_coeff};
    
    iir_filter(signal, ffc, fbc, output);
}

arma::vec one_pole_filter(const arma::vec &signal, double ff_coeff, double fb_coeff) {
    arma::vec output(signal.n_elem);

    one_pole_filter(signal, ff_coeff, fb_coeff, output);
    return output;
}