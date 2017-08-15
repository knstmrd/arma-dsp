#ifndef arma_dsp_helpers_hpp
#define arma_dsp_helpers_hpp

#include <armadillo>

arma::vec reverse(arma::vec a);
arma::vec reverse_copy(const arma::vec &a);
arma::vec pad_zeros(const arma::vec &a, unsigned int n_zeros, bool end=true); // pad with zeros

#endif