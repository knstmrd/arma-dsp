#ifndef arma_dsp_filters_hpp
#define arma_dsp_filters_hpp

#include <armadillo>
#include <cmath>

/*
====Generic FIR filters===
*/

namespace adsp {
    void fir_filter(const arma::vec &signal, const arma::vec &reverse_ff_coeffs, arma::vec &output);
    // implements a FIR filter:
    // y[n] = ff_coeffs[0] * x[n] + ff_coeffs[1] * x[n - 1] + ...
    // however, here the ff_coeffs array is reversed, because armadillo does not understand reverse subvec views
    // so y[n] = reverse_ff_coeffs[filter_order] * x[n] + reverse_ff_coeffs[filter_order - 1] * x[n-1] + ...
    // and this can be written via dot products
    // the result is written to the vector output

    void fir_filter(const arma::vec &signal, double input_gain, double ff_coeff, unsigned int delay, arma::vec &output);
    // y[n] = input_gain * x[n] + ff_coeff * x[n - delay]

    arma::vec fir_filter(const arma::vec &signal, const arma::vec &ff_coeffs);
    // y[n] = ff_coeffs[0] * x[n] + ff_coeffs[1] * x[n - 1] + ....

    arma::vec fir_filter(const arma::vec &signal, double input_gain, double ff_coeff, unsigned int delay);
    // y[n] = input_gain * x[n] + ff_coeff * x[n - delay]

    /*
    ====Generic IIR filters===
    */

    void iir_filter(const arma::vec &signal, const arma::vec &reverse_ff_coeffs, const arma::vec &reverse_fb_coeffs, arma::vec &output);
    // implements an IIR filter:
    // y[n] = ff_coeff[0] * x[n] + ff_coeff[1] * x[n - 1] + ... - fb_coeffs[0] * y[n-1] - fb_coeffs[1] * y[n-2] + ...
    // however, here the ff_coeffs and fb_coeffs arrays are reversed, because armadillo does not understand reverse subvec views
    // so y[n] = reverse_ff_coeffs[ff_filter_order] * x[n] + reverse_ff_coeffs[ff_filter_order - 1] * x[n-1] + ... - reverse_fb_coeffs[fb_filter_order-1] * y[n-1] - ...
    // and this can be written via dot products
    // the result is written to the vector output

    void iir_filter(const arma::vec &signal, double input_gain, double ff_coeff, unsigned int ff_delay, double fb_coeff, unsigned int fb_delay, arma::vec &output);
    // y[n] = input_gain * x[n] + ff_coeff * x[n - ff_delay] - fb_coeff * y[n - fb_delay]

    arma::vec iir_filter(const arma::vec &signal, const arma::vec &ff_coeffs, const arma::vec &fb_coeffs);
    // y[n] = ff_coeff[0] * x[n] + ff_coeff[1] * x[n - 1] + ... - fb_coeffs[0] * y[n-1] - fb_coeffs[1] * y[n-2] + ...

    arma::vec iir_filter(const arma::vec &signal, double input_gain, double ff_coeff, unsigned int ff_delay, double fb_coeff, unsigned int fb_delay);
    // y[n] = input_gain * x[n] + ff_coeff * x[n - ff_delay] - fb_coeff * y[n - fb_delay]

    /*
    ====Zero- and pole- filters===
    */

    void one_zero_filter(const arma::vec &signal, double input_gain, double ff_coeff, arma::vec &output);
    // y[n] = input_gain * x[n] + ff_coeff * x[n-1]

    arma::vec one_zero_filter(const arma::vec &signal, double input_gain, double ff_coeff);
    // y[n] = input_gain * x[n] + ff_coeff * x[n-1]

    void one_pole_filter(const arma::vec &signal, double input_gain, double fb_coeff, arma::vec &output);
    // y[n] = ff_coeff * x[n] - fb_coeff * y[n-1]

    arma::vec one_pole_filter(const arma::vec &signal, double input_gain, double fb_coeff);
    // y[n] = ff_coeff * x[n] - fb_coeff * y[n-1]

    void two_pole_resonator(const arma::vec &signal, unsigned int sampling_rate, double frequency, double bandwidth, arma::vec &output);

    arma::vec two_pole_resonator(const arma::vec &signal, unsigned int sampling_rate, double frequency, double bandwidth);
    // R = exp(-pi * bandwidth / sampling_rate)
    // a1 = -2 * R * cos(2 * pi * frequency / sampling_rate)
    // a2 = R^2

    /*
    ====All-/low-/high-/band-pass filters===
    */

    void allpass_filter(const arma::vec &signal, double gain, unsigned int delay, arma::vec &output);

    arma::vec allpass_filter(const arma::vec &signal, double gain, unsigned int delay);

    void lowpass_filter(const arma::vec &signal, unsigned int sampling_rate, double cutoff_frequency, arma::vec &output);
    // not cutoff, but actually knee frequency
    // y[n] = alpha * x[n] + (1-alpha) * y[n-1]
    // alpha = 2 pi dt * cutoff_frequency / (2 * pi * dt * cutoff_frequency + 1)
    // dt = 1 / sampling_rate

    arma::vec lowpass_filter(const arma::vec &signal, unsigned int sampling_rate, double cutoff_frequency);

    // comb filter - wrapped call to iir_filter
    // highpass
    // bandpass
}
#endif