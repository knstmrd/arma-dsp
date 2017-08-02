#include "filters.hpp"

arma::vec fir_filter(const arma::vec &signal, const arma::vec &ff_coeffs) {
    arma::vec output(signal.n_elem);

    int i;
    for (i=0; i<ff_coeffs.n_elem; i++) {
        output[i] = arma::dot(signal.subvec(i, 0), ff_coeffs.subvec(0, i)); // TODO: Does reversing indices work?
    }

    for (i=ff_coeffs.n_elem; i<signal.n_elem; i++) {
        output[i] = arma::dot(signal.subvec(i, i - signal.n_elem + 1), ff_coeffs); // TODO: Does reversing indices work?
    }

    return output;
}

arma::vec iir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, const arma::vec &fb_coeffs) {
    output = fir_filter(signal, ff_coeffs);

    int i;

    for (i=1; i<=fb_coeffs.n_elem; i++) {
        output[i] -= arma::dot(output.subvec(i-1, 0), fb_coeffs.subvec(0, i-1));
    }

    for (i=fb_coeffs.n_elem+1; i<=signal.n_elem; i++) {
        output[i] = arma::dot(signal.subvec(i-1, i - signal.n_elem + 1), fb_coeffs);
    }

    return output;
}