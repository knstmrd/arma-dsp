#include "helpers.hpp"
#include <algorithm> 

arma::vec reverse(arma::vec a) {
    std::reverse(a.begin(), a.end());
    return a;
}

arma::vec reverse_copy(const arma::vec &a) {
    arma::vec b = a;
    std::reverse(b.begin(), b.end());
    return b;
}

arma::rowvec reverse_copy(const arma::rowvec &a) {
    arma::rowvec b = a;
    std::reverse(b.begin(), b.end());
    return b;
}

arma::cx_rowvec reverse_copy(const arma::cx_rowvec &a) {
    arma::cx_rowvec b = a;
    std::reverse(b.begin(), b.end());
    return b;
}

arma::vec pad_zeros(const arma::vec &a, unsigned int n_zeros, bool end) {
    arma::vec b = arma::zeros(a.n_elem + n_zeros);
    if (end) {
        b.subvec(0, a.n_elem-1) = a;
    }
    else {
        b.subvec(n_zeros, b.n_elem-1) = a;
    }
    return b;
}