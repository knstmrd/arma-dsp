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