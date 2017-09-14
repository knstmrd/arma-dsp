#include "windows.hpp"
#include "helpers.hpp"

arma::vec adsp::window_rectangular(unsigned int framelength) {
    return arma::ones(framelength);
}

arma::vec adsp::window_triangle(unsigned int framelength) {
    if (framelength == 1) {
        return arma::ones(1);
    }
    else {
        arma::vec result = arma::vec(framelength);
        int half_length = (int)((framelength + 1) / 2);
        arma::vec n = arma::regspace<arma::vec>(1, half_length);
        if ((int)(framelength % 2) == 0) {
            n = (2.0 * n - 1.0) / framelength;
            result.subvec(0, half_length-1) = n;
            result.subvec(half_length, framelength-1) = reverse(n.subvec(0, half_length-1));
        }
        else {
            n = 2.0 * n / (framelength + 1.0);
            result.subvec(0, half_length-1) = n;
            result.subvec(half_length, framelength-1) = reverse(n.subvec(0, half_length-2));
        }
        return result;
    }
}

arma::vec adsp::window_welch(unsigned int framelength) {
    if (framelength == 1) {
        return arma::ones(1);
    }
    else {
        arma::vec n = arma::linspace<arma::vec>(0, framelength-1, framelength) - (framelength - 1.0) / 2.0;
        return 1 - (n / ((framelength - 1.0) / 2.0)) % (n / ((framelength - 1.0) / 2.0));
    }
}

arma::vec adsp::window_gaussian(unsigned int framelength, double sigma) {
    if (framelength == 1) {
        return arma::ones(1);
    }
    else {
        arma::vec n = arma::linspace<arma::vec>(0, framelength-1, framelength) - (framelength - 1.0) / 2.0;
        return arma::exp(-n % n / (2 * sigma * sigma));
    }
}


arma::vec adsp::window_hann(unsigned int framelength) {
    if (framelength == 1) {
        return arma::ones(1);
    }
    else {
        arma::vec n = arma::linspace<arma::vec>(0, framelength-1, framelength);
        return 0.5 - 0.5 * arma::cos(2 * n * M_PI / (framelength - 1));
    }
}

arma::vec adsp::window_hamming(unsigned int framelength) {
    if (framelength == 1) {
        return arma::ones(1);
    }
    else {
        arma::vec n = arma::linspace<arma::vec>(0, framelength-1, framelength);
        return 0.54 - 0.46 * arma::cos(2 * n * M_PI / (framelength - 1));
    }
}

arma::vec adsp::window_blackman(unsigned int framelength, double alpha) {
    if (framelength == 1) {
        return arma::ones(1);
    }
    else {
        arma::vec n = arma::linspace<arma::vec>(0, framelength-1, framelength);
        return (1.0 - alpha) / 2.0 - 0.5 * arma::cos(2 * n * M_PI / (framelength - 1)) + 0.5 * alpha * arma::cos(4 * n * M_PI / (framelength - 1));
    }
}