#ifndef ImageClass_H
#define ImageClass_H
//#include "Filter.hpp"
#include <iostream>
#include <vector>

/*!
 * @class ImageClass
 * @brief Class for the storage of information relative to an image, and
 * functions for the application of a filter by convolution
 */
class ImageClass
{
public:

/*!
 * @brief Constructor for the ImageClass object
 * @param rows the number of rows in the image, generally the image's height
 * @param cols, the number of columns in the image, generally the image's width
 * @param, pixels, a vector containing the intensity values of the image pixels,
 * the representation in row based
 */
ImageClass(int rows, int cols, std::vector<u_char> pixels); //default constructor


/*!
 * @brief get the number of columns in the image
 * @return the number of columns
 */
int get_ncol();
/*!
 * @brief get the number of rows in the image
 * @return the number of rows
 */
int get_nrows();
/*!
 * @brief get the intensity of the pixel
 * @param x is the column coordonate of the pixel
 * @param y is the row coordonate of the pixel
 * @return the intensity of the pixel at the (x,y) coordonate
 */
int get_intensity(int x, int y);
/*!
 * @brief get the pixels intensities of the entire image
 * @return the vector that contain all the pixels of my image
 */
std::vector<u_char> get_pixels();
/*!
 * @brief give the value of the convolution between the pixel at the x, y coordinates
 * and the selected filter.
 * The filter is applied by the dot product between the filter and the surrounding pixels
 * The zero padding is obtained with the boolean method isInBounds
 * @param x is the column coordonate of the pixel
 * @param y is the row coordonate of the pixel
 * @param filter is a 1D array of the row based filter applied on the image.
 * @return the value of the convolution between the filter applied on the (x,y) coordonate
 */
int convolve(int x, int y, std::vector<int> filter);
/*!
 * @brief check if the selected coordonate is inside frame of the image, if not return false.
 * @param x is the column coordonate of the pixel
 * @param y is the row coordonate of the pixel
 * @return true if inside the boundary of the image, false if not.
 */

int noise(int x, int y);

std::vector<u_char> noise_filtering();

bool isInBounds(int x, int y);
/*!
 * @brief display the intensity distribution of the image, per channel.
 * Create a text file that contains the values of the number of pixels per intensity.
 * The intensity distribution is ploted with the python script histogram.py
 */
void histogram(std::string title);
/*!
 * @brief set intensity of the image at the selected coordonate.
 * The modified array is img_copy as to always keep an original array of the image.
 *does not return anything but change the values of img_copy
 * @param x is the column coordonate of the pixel
 * @param y is the row coordonate of the pixel
 * @param i is the value of the set intensity.
 */
void set_intensity(int x, int y, int i);

void set_pixel_intensity(int x, int y, int i);
/*!
 * @brief iterate on each pixel of the image and applied the convolution with the provided filter.
 * @param filter is a 1D array of the row based filter applied on the image.
 * @return the vector that contains the values of the filtered image.
 */
std::vector<u_char> filtering(std::vector<int> filter);

private:
  int rows;
  int cols;

  std::vector<u_char> pixels;
  std::vector<u_char> img_copy;
};


#endif
