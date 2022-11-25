#include "ImageClass.hpp"
#include "FFTcalcul.h"
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>
#include "gtest/gtest.h"


TEST(ImageClassTest, image_convolution)
{
  std::vector<u_char> imagetest_v{1,0,1,0,1,0,1,0,1,0};
  ImageClass imagetest(3,3,imagetest_v);
  //size of the image I created for this test, it is a 3*3 matrix with the values of imagetest_v
  std::vector<int> filter {0,1,0,1,0,1,0,1,0};
  int convolution = imagetest.convolve(1,1,filter);

  EXPECT_EQ(0, convolution);
  // We are expecting 0 for the convolution value as the scalar produce is 0 by hand.
}

TEST(ImageClassTest, is_In_Bounds)
{
  std::vector<u_char> imagetest_v(2500,0);
  ImageClass imagetest(50, 50, imagetest_v);

  ASSERT_TRUE(imagetest.isInBounds(10,10));

  ASSERT_FALSE(imagetest.isInBounds(-1,10));

  ASSERT_FALSE(imagetest.isInBounds(60,50));
  // We are expecting 0 for the convolution value as the scalar produce is 0 by hand.
}

TEST(ImageClassTest, get_Intensity)
{
  std::vector<u_char> imagetest_v(2500,0);
  ImageClass imagetest(50, 50, imagetest_v);
  imagetest.set_pixel_intensity(10,10,4);
  EXPECT_EQ(4, imagetest.get_intensity(10,10));
  // We are expecting an intensity of 0, as the image intensities are all 0.
}

TEST(FFTcalculTest, FFT2D)
{
    int n=32;
    double *fRe= new double[n*n*3],*fIm= new double[n*n*3];
    for (int i=1;i<n*n*3;i++) {
        fRe[i]=i*3; // initialize random array
    }
    double *FRe= new double[n*n*3], *FIm= new double[n*n*3];
    double *fRe2 = new double[n*n*3], *fIm2 = new double[n*n*3];
    FFTcalcul::FFT2D(n,n,fRe,fIm,FRe,FIm);
    FFTcalcul::FFT2D(n,n,FRe,FIm,fRe2,fIm2,true);

    for (int i=1;i<n*n*3;i++) {
        EXPECT_EQ(round(fRe[i]), round(fRe2[i])); // Transformed array should be the same as the original
    }
}

TEST(FFTcalculTest, blur){
    int n=16;
    double *fRe= new double[n*n*3];
    for (int i=1;i<n*n*3;i++) {
        fRe[i]=10; // initialize random array
    }
    double *fReFilt=FFTcalcul::blur(fRe,2,n,n,1);// 10% unselected circle
    EXPECT_EQ(0,fReFilt[n*n*3/2]); // middle point, with the shift it is the corner
}


int main(int argc, char **argv){
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
