#include "helper.hpp"

cv::Mat load_image(std::string image_path)
{
  Mat image = imread(image_path, IMREAD_COLOR);
  if(image.empty())
  {
      std::cout << "Could not read the image: " << image_path << std::endl;
  }
  return image;
}

void display_im(cv::Mat image, std::string title)
{
    imshow(title, image);
    int k = cv::waitKey(0);
}

std::vector<uchar> cv_to_vector(Mat image)
{
  //assume single channel 2D matrix.
  std::vector<uchar> array;

  if (image.isContinuous()) {
    //array.assign(image.datastart, image.dataend); // <- has problems for sub-imagerix like image = big_image.row(i)
    array.assign(image.data, image.data + image.total()*image.channels());
  } else {
    for (int i = 0; i < image.rows; ++i) {
      array.insert(array.end(), image.ptr<uchar>(i), image.ptr<uchar>(i)+image.cols*image.channels());
    }
  }

  return array;
}

std::vector<Mat> split_channels(Mat image)
{
  Mat ch1, ch2, ch3;
  // "channels" is a vector of 3 Mat arrays:
  std::vector<Mat> channels(3);
  // split img:
  split(image, channels);
  // get the channels (dont forget they follow BGR order in OpenCV)

  ch1 = channels[0];
  ch2 = channels[1];
  ch3 = channels[2];


  return channels;

}



std::vector<std::vector<uchar>> channels_to_vectors(Mat image)
{

  std::vector<Mat> channels = split_channels(image);
  std::vector<uchar> ch1_v = cv_to_vector(channels[0]);
  std::vector<uchar> ch2_v = cv_to_vector(channels[1]);
  std::vector<uchar> ch3_v = cv_to_vector(channels[2]);

  std::vector<std::vector<uchar>> im_vec {ch1_v, ch2_v, ch3_v};

  return im_vec;

}


cv::Mat vec_to_cv(std::vector<uchar> vec, int rows, int cols){

  Mat img = Mat(rows, cols, CV_8UC1); // initialize matrix of uchar of 1-channel where you will store vec data

  /*
  Mat g = Mat(rows, cols, CV_8UC1);
  Mat b = Mat(rows, cols, CV_8UC1);
  */
  //copy vector to mat
  memcpy(img.data, vec.data(), vec.size()*sizeof(uchar)); // change uchar to any type of data values that you want to use instead

  /*
  memcpy(g.data, vec[1].data(), vec[1].size()*sizeof(uchar));
  memcpy(b.data, vec[2].data(), vec[2].size()*sizeof(uchar));


  std::vector<Mat> channels;
  channels.push_back(r);
  channels.push_back(g);
  channels.push_back(b);

  Mat img_col;
  cv::merge(channels, img_col);

  */

  return img;

}
// single chanel 3D array
double *cv_to_pointer(cv::Mat image) {
    double H = image.rows, W = image.cols, c = 3;
    double * ptr;
    ptr=(new double[(int)(H*W*c)]);

    for (int i=0;i<W*H*c;i++){
        int x,y,indexc;
        y=(int)floor((double)i/(W*c));
        x=(int)(floor((double)i/c))%(int)W;
        indexc=i%3;

        ptr[i]=static_cast<double>(image.at<cv::Vec3b>(cv::Point(x,y))[indexc]);
    }

    return ptr;

}
// Set the rest of the color to 0 to have a power of 2 squared image if it isn't the case. Only way for the fft algorithm to work
cv::Mat load_square_image(std::string image_path) {
    /*!
     *
     */
    cv::Mat image = load_image(image_path);

    int H = image.rows, W = image.cols;
    int square_size = max(H, W);
    int log_2 = ceil(log2(square_size));
    square_size = pow(2, log_2);
    cv::Mat sqrt_im(square_size, square_size, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int y = 0; y < H; y++)
          for (int x = 0; x < W; x++) {
              cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x, y));
              sqrt_im.at<cv::Vec3b>(cv::Point(x, y)) = color;
        }
    for (int y = H; y < square_size; y++)
        for (int x = W; x < square_size; x++) {
              cv::Vec3b color = sqrt_im.at<cv::Vec3b>(cv::Point(x, y));
              for (int i = 0; i < 3; i++) {
                  color[i] = 0;
              }
              sqrt_im.at<cv::Vec3b>(cv::Point(x, y)) = color;
          }
    return sqrt_im;
}
