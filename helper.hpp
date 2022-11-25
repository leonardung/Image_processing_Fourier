#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;
/*!
 * @brief load the image with opencv
 * @param image_path is the path to the image.
 * @return an openCv image.
 */
cv::Mat load_image(std::string image_path);
/*!
 * @brief display the image.
 * @param image, the image loaded with openCv
 * imshow is an OpenCv fonction, only used to the display the image on screen.
 */

void display_im(cv::Mat, std::string title);
/*!
 * @brief store the openCV values in our own vector.
 * @param image, the image loaded with openCv
 */
std::vector<uchar> cv_to_vector(cv::Mat image);
/*!
 * @brief split the image into three channels: Blue, Green, Red.
 * @param image, the image loaded with openCv
 * @return the three channels.
 */
std::vector<Mat> split_channels(cv::Mat image);
/*!
 * @brief calls split_channels to obtain the three openCV channels and uses the function cv_to_vector to store the channels intensity values in our own data structure.
 * @param image, the image loaded with openCv
 * @return the three channels in our own data structure (three 1D vectors size:rows*cols).
 */
std::vector<std::vector<uchar>> channels_to_vectors(cv::Mat image);
/*!
 * @brief convert the array from our image class to an openCV object for displaying purpose only.
 * @param the array from our image class.
 * @param rows, the number of rows of the image.
 * @param cols, the number of columns of the image.
 * @return the image as an openCV object.
 */
cv::Mat vec_to_cv(std::vector<uchar> vec, int rows, int cols);

/*!
 * @brief transform an image Mat into an array
 * @param image
 * @return the pointer in which the array of the image is stored
 */
double *cv_to_pointer(cv::Mat image);

/*!
 * @brief Load and transform an image to a square image of a size of power of 2.
 * To fill the square image, the rest of the values will be set to zero.
 * @param image_path local path where the image is saved
 * @return a square image Mat
 */
cv::Mat load_square_image(std::string image_path);

#endif
