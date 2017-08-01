#include "windows.hpp"

arma::vec window_rectangular(int framelength) {
    return arma::ones(framelength);
}

arma::vec window_gaussian(int framelength, double sigma) {
    if (framelength == 1) {
        return arma::ones(1);
    }
    else {
        arma::vec n = arma::linspace<arma::vec>(0, framelength-1, framelength) - (framelength - 1.0) / 2.0;
        return arma::exp(-n * n / (2 * sigma * sigma));
    }
    // TODO: add framelength checks
}

arma::vec window_hann(int framelength) {
    if (framelength == 1) {
        return arma::ones(1);
    }
    else {
        arma::vec n = arma::linspace<arma::vec>(0, framelength-1, framelength);
        return 0.5 - 0.5 * arma::cos(2 * n * M_PI / (framelength - 1));
    }
    // TODO: add framelength checks
}

arma::vec window_hamming(int framelength) {
    if (framelength == 1) {
        return arma::ones(1);
    }
    else {
        arma::vec n = arma::linspace<arma::vec>(0, framelength-1, framelength);
        return 0.54 - 0.46 * arma::cos(2 * n * M_PI / (framelength - 1));
    }
    // TODO: add framelength checks
}

arma::vec window_blackman(int framelength, double alpha) {
    if (framelength == 1) {
        return arma::ones(1);
    }
    else {
        arma::vec n = arma::linspace<arma::vec>(0, framelength-1, framelength);
        return (1.0 - alpha / 2.0) - 0.5 * arma::cos(2 * n * M_PI / (framelength - 1)) + 0.5 * alpha * arma::cos(4 * n * M_PI / (framelength - 1));
    }
    // TODO: add framelength checks
}