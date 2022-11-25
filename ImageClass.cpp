#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <numeric>
#include <algorithm>
#include "ImageClass.hpp"


ImageClass::ImageClass(int rows, int cols, std::vector<u_char> pixels)
  :rows(rows), cols(cols), pixels(pixels), img_copy(pixels)
{

}

int ImageClass::get_ncol(){return cols;}
int ImageClass::get_nrows(){return rows;}

std::vector<u_char> ImageClass::get_pixels(){return pixels;}

int ImageClass::get_intensity(int x, int y)
{
  int index = cols*y + x;
  return pixels[index];
}


void ImageClass::histogram(std::string title)
{

  std::vector<int> bins(255, 0);

  for (int item : pixels) {
    bins[item] += 1;
 }


  std::ofstream histogram("../histogram.txt");
  std::ostream_iterator<int> output_iterator(histogram, ",");
  std::copy(bins.begin(), bins.end(), output_iterator);

  histogram.close();

  std::string str = "python ../plot_histogram.py" + title;
  const char *command = str.c_str();


  system(command);
}



void ImageClass::set_intensity(int x, int y, int i)
{
  int index = cols*y + x;
  img_copy[index] = i;
}

void ImageClass::set_pixel_intensity(int x, int y, int i)
{
  int index = cols*y + x;
  pixels[index] = i;
}

bool ImageClass::isInBounds(int x, int y)
{
  bool inBounds = true;

  if (x < 0 || y <0 || x > cols || y > rows) {
    inBounds = false;
  }

  return inBounds;
}

std::vector<u_char> ImageClass::filtering(std::vector<int> filter)
{
  for (int x = 0; x < cols; x++) {
    for (int y = 0; y < rows; y++) {
        set_intensity(x, y, convolve(x,y,filter));
      }
    }
    return img_copy;
  }




int ImageClass::convolve(int x, int y, std::vector<int> filter)
{

  std::vector<int> tmp(9,0);
  int k=0; //index of tmp in which to store the value
  for (int i = -1; i < 2; i++) {
      for (int j = -1; j < 2; j++) {
        if (isInBounds(x, y)) {
          tmp[k] = get_intensity(x + i, y + j);
        }

        k += 1;
      }
    }

    int convolution = std::inner_product(filter.begin(), filter.end(), tmp.begin(), 0);
    return convolution;
}


std::vector<u_char> ImageClass::noise_filtering()
{
  for (int x = 0; x < cols; x++) {
    for (int y = 0; y < rows; y++) {
        set_intensity(x, y, noise(x,y));

      }
    }

    return img_copy;
  }



int ImageClass::noise(int x, int y)
{

  std::vector<int> tmp(9,0);
  int k=0; //index of tmp in which to store the value
  for (int i = -1; i < 2; i++) {
      for (int j = -1; j < 2; j++) {
        if (isInBounds(x, y)) {
          tmp[k] = get_intensity(x + i, y + j);
        }
        k += 1;
      }
    }

  size_t size = tmp.size();

  if (size == 0)
  {
    return 0;
  }

  else {
    sort(tmp.begin(), tmp.end());
    if (size % 2 == 0)
    {
      return (tmp[size/2-1] + tmp[size/2])/2;
    }
    else
    {
      return tmp[size/2];
    }
  }


}
