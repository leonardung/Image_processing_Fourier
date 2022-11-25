#include "helper.hpp"
#include "ImageClass.hpp"
#include "imageFourierClass.hpp"

using namespace std;
using namespace cv;


int main()
{

  string image_path = "../256.png";
  //string image_path = "photo2.png"; // not square

  cv::Mat image = load_square_image(image_path);

  cv::Mat sinus = imageFourierClass::create_sin_image(128);

  imageFourierClass::display_fourier(sinus, "sinus");

  imageFourierClass::display_fourier(image, image_path);

  destroyAllWindows();

  imageFourierClass::choose_filter(image);

  //========================================
  //          IMAGE LOADING
  //========================================

  std::string lena_path = "../lena.png";
  std::string shadow_path = "../shadows.jpg";

  cv::Mat lena = load_image(lena_path);
  cv::Mat lena_grayscale;

  cv::Mat shadows = load_image(shadow_path);


  std::vector<Mat> lena_channels = split_channels(lena);
  cv::Mat lena_red = lena_channels[2];
  cv::Mat lena_green = lena_channels[1];
  cv::Mat lena_blue = lena_channels[0];

  cv::cvtColor(lena, lena_grayscale, cv::COLOR_BGR2GRAY);
  cv::cvtColor(shadows, shadows, cv::COLOR_BGR2GRAY);

  std::vector<uchar> shadows_vec = cv_to_vector(shadows);

  std::vector<uchar> lena_vec = cv_to_vector(lena_grayscale);

  std::vector<uchar> lena_red_vec = cv_to_vector(lena_red);
  std::vector<uchar> lena_blue_vec = cv_to_vector(lena_blue);
  std::vector<uchar> lena_green_vec = cv_to_vector(lena_green);

  int rows = lena_grayscale.rows;
  int cols = lena_grayscale.cols;

  ImageClass lena_gray_image(rows, cols, lena_vec);

  ImageClass lena_red_image(rows, cols, lena_red_vec);
  ImageClass lena_blue_image(rows, cols, lena_blue_vec);
  ImageClass lena_green_image(rows, cols, lena_green_vec);

  int s_rows = shadows.rows;
  int s_cols = shadows.cols;

  ImageClass shadows_image(s_rows, s_cols, shadows_vec);

  std::string dummy_title = "titre";
  /*
  display_im(vec_to_cv(lena_gray_image.get_pixels(), lena_gray_image.get_nrows(),
                        lena_gray_image.get_ncol()), dummy_title);
*/
  cv::imshow("Lena", lena);
  int k = cv::waitKey(0);

  //========================================
  //      HISTOGRAM
  //========================================

  lena_gray_image.histogram(" grayscale image histogram");

  lena_red_image.histogram(" red_histogram");
  lena_green_image.histogram(" blue_histogram");
  lena_blue_image.histogram(" green_histogram");



  //========================================
  //      FILTER DECLARATION
  //========================================

  std::vector<int> prewitt_h{-1, 0, 1, -1, 0, 1, -1, 0, 1}; // horizontal prewitt

  std::vector<int> prewitt_v{1, 1, 1, 0, 0, 0, -1, -1, -1}; // vertical prewitt

  std::vector<int> high_pass{0, -1, 0, -1, 5, -1, 0, -1, 0}; // high pass filter


  //========================================
  //  DISPLAY FILTERED IMAGES
  //========================================

  display_im(vec_to_cv(lena_gray_image.get_pixels(), lena_gray_image.get_nrows(),
                        lena_gray_image.get_ncol()), "gray Lena");



  ImageClass filtered_h(rows, cols, lena_gray_image.filtering(prewitt_v));

  display_im(vec_to_cv(filtered_h.get_pixels(), filtered_h.get_nrows(),
                        filtered_h.get_ncol()), "horizontal edge detection with prewitt, Lena");

  ImageClass filtered_v(rows, cols, lena_gray_image.filtering(prewitt_h));

  display_im(vec_to_cv(filtered_v.get_pixels(), filtered_v.get_nrows(),
                        filtered_v.get_ncol()), "vertical edge detection with prewitt, Lena");


  ImageClass image_high(rows, cols, lena_gray_image.filtering(high_pass));

  display_im(vec_to_cv(image_high.get_pixels(), image_high.get_nrows(),
                        image_high.get_ncol()), "high pass Lena");

  ImageClass filtered_noise(rows, cols, image_high.noise_filtering());

  display_im(vec_to_cv(filtered_noise.get_pixels(), filtered_noise.get_nrows(),
                      filtered_noise.get_ncol()), "noise filtering Lena");


  display_im(vec_to_cv(shadows_image.get_pixels(), shadows_image.get_nrows(),
                        shadows_image.get_ncol()), "hand shadows");

  ImageClass shadows_edge(s_rows,s_cols, shadows_image.filtering(prewitt_h));

  display_im(vec_to_cv(shadows_edge.get_pixels(), shadows_edge.get_nrows(),
                        shadows_edge.get_ncol()), "hand shadows edge");



}
