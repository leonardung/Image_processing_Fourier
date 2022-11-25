//
// Created by leonard on 22.01.21.
//

#ifndef PROJECT_FFTCALCUL_H
#define PROJECT_FFTCALCUL_H
#include "helper.hpp"

class FFTcalcul {
public:
    /*!
 * @brief 1D Fast Fourier transform that work non recursively
 * @param n size of the array to be transformed
 * @param inverse if it calculate the inverse of fft or not
 * @param fRe input of the real part of the array
 * @param fIm input of the imaginary part of the array
 * @param FRe output of the real part of the transformed array
 * @param FIm output of the imaginary part of the transformed array
 * @param step the row size to work on a column
 * @param factor the value to divide the result with
 */
    static void
    FFT(int n, bool inverse, const double *fRe, const double *fIm, double *FRe, double *FIm, int step, double factor);

    /*!
    * @brief 2D Fast Fourier transform that calls the 1D FFT for each row and each column
    * @param w weight of the image
    * @param h height of the image
    * @param fRe input of the real part of the image
    * @param fIm input of the imaginary part of the image
    * @param FRe output of the real part of the transformed image
    * @param FIm output of the imaginary part of the transformed image
    * @param inverse if it calculate the inverse of fft or not
    */
    static void FFT2D(int w, int h, const double *fRe, const double *fIm, double *FRe, double *FIm, bool inverse = false);

    /*!
     * @brief Calculates the amplitude of a complex number Amp = sqrt(fRe²+fIm²)
     * @param w weight of the image
     * @param h height of the image
     * @param fAmp output of the calculated amplitude
     * @param fRe input of the real part of the image
     * @param fIm input of the imaginary part of the image
     */
    static void calculateAmp(int w, int h, double *fAmp, const double *fRe, const double *fIm);

    /*!
 * @brief add a filter to an image by selecting only a portion of the transformed image
 * @param f array of fourier transformed image
 * @param radius1 factor which the radius will be divided by
 * @param W weight of the image
 * @param H height of the image
 * @param pass filter type (1 = low pass filter ; 2 = high pass filter ; 3 = select band pass)
 * @param radius2 factor which the 2nd radius will by divided by (only used for filer type 3 and 4), by default 0
 * @return array of same size in which the unselected value are 0
 */
    static double* blur(double *f, double radius1, int H, int W, int pass, double radius2=0);
};


#endif //PROJECT_FFTCALCUL_H
