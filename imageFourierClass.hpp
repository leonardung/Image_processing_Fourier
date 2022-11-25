//
// Created by leonard on 26.12.20.
//

#ifndef imageFourierClass_H
#define imageFourierClass_H


#include "helper.hpp"
#include "FFTcalcul.h"


class imageFourierClass {



    /*!
    * @brief Create an image Mat from an array of size (w * h * 3)
    * @param w weight of the image
    * @param h height of the image
    * @param f array to be transformed to an image
    * @param shift true if the image to create is a fourier transform
    * @return image Mat
    */
    static cv::Mat draw(int w, int h, const double *f, bool shift);



    /*!
     * @brief Put together 3 images in one window
     * @param real image of the real part
     * @param im image of the imaginary part
     * @param amp image of the amplitude
     * @param title
     */
    static void display_real_im_amp(cv::Mat real, cv::Mat im, cv::Mat amp, std::string title);

    /*!
     * @brief display a window with the applied pass (real part, imaginary part, image with filter applied)
     * @param image
     * @param radius1 factor which the radius will be divided by
     * @param pass filter type (1 = low pass filter ; 2 = high pass filter ; 3 = select band pass)
     * @param radius2 factor which the 2nd radius will by divided by (only for filer type 3 and 4)
     */
    static void display_blur(cv::Mat image, double radius1, int pass, double radius2=0);



public:

    /*!
     * @brief It will display 3 windows of 3 images (real part, imaginary part, amplitude);
     * 1st window is the untransformed image (imaginary part should be zero),
     * 2nd window is the fourier transformed image
     * 3rd window is the re-transformed image by the inverse fourier transform (it should be same as the untransformed window)
     * @param image
     * @param title name of the picture
     */
    static void display_fourier(cv::Mat image, std::string title);

    /*!
     * @brief create a sinusoidal image to check if the fft works
     * @param size number of rows and columns (are equal)
     * @return image Mat
     */
    static cv::Mat create_sin_image(int size);

    /*!
     * @brief interaction with the user to choose a filter for an image
     * @param image
     */
    static void choose_filter(cv::Mat image);

};


#endif //TEST_IMAGE_H
