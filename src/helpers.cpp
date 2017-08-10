#include "helpers.hpp"
#include <algorithm> 

arma::vec reverse(arma::vec a) {
    std::reverse(a.begin(), a.end());
    return a;
}