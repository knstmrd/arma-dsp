#include <armadillo>
#include <math>
#include <function>

arma::vec filter(arma::vec signal, arma::vec ff_coeffs, arma::vec fb_coeffs);

arma::vec one_pole_filter(arma::vec signal, double ff_coeff);

arma::vec one_pole_filter(arma::vec signal, double fb_coeff);

arma::vec two_pole_resonator(arma::vec signal, double frequency, double damping);

cx_mat stft(arma::vec signal, arma::vec window_array, int framelength=1024, int overlap=2, bool half=true);

cx_mat stft(arma::vec signal, std::function<arma::vec(int)> window, int framelength=1024, int overlap=2, bool half=true);

cx_mat stft(arma::vec signal, std::function<arma::vec(int, double)> window, int framelength=1024, int overlap=2, bool half=true);

arma::vec window_rectangular(int framelength);
arma::vec window_gaussian(int framelength, double sigma);
arma::vec window_hann(int framelength);
arma::vec window_hamming(int framelength);
arma::vec window_blackman(int framelength, double alpha);