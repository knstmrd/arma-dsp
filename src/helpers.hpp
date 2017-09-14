#ifndef arma_dsp_helpers_hpp
#define arma_dsp_helpers_hpp

#include <armadillo>

namespace adsp {
    arma::vec reverse(arma::vec a);
    arma::vec reverse_copy(const arma::vec &a);
    arma::rowvec reverse_copy(const arma::rowvec &a);
    arma::cx_rowvec reverse_copy(const arma::cx_rowvec &a);
    arma::vec pad_zeros(const arma::vec &a, unsigned int n_zeros, bool end=true); // pad with zeros
} // adsp


#endif