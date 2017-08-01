#include "filters.hpp"

arma::vec fir_filter(arma::vec signal, arma::vec ff_coeffs) {
    arma::vec output(signal.n_elem);

    int i;
    for (i=0; i<ff_coeffs.n_elem; i++) {
        output[i] = arma::dot(signal.subvec(0, i), ff_coeffs.subvec(0, i));
    }

    for (i=ff_coeffs.n_elem; i<signal.n_elem; i++) {
        output[i] = arma::dot(signal.subvec(i - signal.n_elem + 1, i), ff_coeffs);
    }

    return output;
}