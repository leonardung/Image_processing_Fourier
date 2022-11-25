//
// Created by leonard on 26.12.20.
//

#include "imageFourierClass.hpp"



cv::Mat imageFourierClass::draw(int w, int h, const double *f, bool shift)
{
    cv::Mat fourier(w, h, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int y1 = 0; y1 < h; y1++)
        for(int x1 = 0; x1 < w; x1++)
        {
            int x = x1, y = y1;
            if(shift) { // Shift corners to center for the visualisation of fourier transform
                x = (x1 + w / 2) % w; y = (y1 + h / 2) % h;
            }
            cv::Vec3b color = fourier.at<cv::Vec3b>(cv::Point(x1,y1));

            for(int i = 0; i < 3; i++) {
                // calculate color values out of the array
                color[i] = int(f[3 * w * y + 3 * x + i]);

                // negative colors set to 0
                if (int(f[3 * w * y + 3 * x + i]) < 0) color[i] = 0;

                // set color components higher than 255 to 255
                if (int(f[3 * w * y + 3 * x + i]) > 255) color[i] = 255;

            }
            fourier.at<cv::Vec3b>(cv::Point(x1,y1))=color;
        }
    return fourier;
}

// Display 3 images in a single window (real part, imaginary part, amplitude)
void imageFourierClass::display_real_im_amp(cv::Mat real, cv::Mat im, cv::Mat amp, std::string title) {
    cv::Mat matDst(cv::Size(real.cols * 3, real.rows), real.type(), cv::Scalar::all(0));
    cv::Mat matRoi = matDst(cv::Rect(0, 0, real.cols, real.rows));
    real.copyTo(matRoi);
    matRoi = matDst(cv::Rect(real.cols, 0, real.cols, real.rows));
    im.copyTo(matRoi);
    matRoi = matDst(cv::Rect(real.cols * 2, 0, real.cols, real.rows));
    amp.copyTo(matRoi);
    display_im(matDst, title);
    matDst.release();
    matRoi.release();
}


void imageFourierClass::display_fourier(cv::Mat image, std::string title) {
    int H = image.rows, W = image.cols, c = 3;
    // pointers that will be needed for the fft
    double *fRe = new double[H * W * c], *fIm = new double[H * W * c], *fAmp = new double[H * W * c];
    double *FRe = new double[H * W * c], *FIm = new double[H * W * c], *FAmp = new double[H * W * c];
    double *fRe2 = new double[H * W * c], *fIm2 = new double[H * W * c], *fAmp2 = new double[H * W * c];

    fRe = cv_to_pointer(image);

    // Draw the image without transformation
    FFTcalcul::calculateAmp(W, H, fAmp, fRe, fIm);
    cv::Mat untransformed_real = imageFourierClass::draw(W, H, fRe, false);
    cv::Mat untransformed_im = imageFourierClass::draw(W, H, fIm, false);
    cv::Mat untransformed_amp = imageFourierClass::draw(W, H, fAmp, false);
    display_real_im_amp(untransformed_real, untransformed_im, untransformed_amp,
                        title + " - Untransformed - (Real, Imaginary, Amplitude)");

    // Calculate and draw FFT
    FFTcalcul::FFT2D(W, H, fRe, fIm, FRe, FIm);
    delete[] fRe;
    delete[] fIm;
    delete[] fAmp;
    FFTcalcul::calculateAmp(W, H, FAmp, FRe, FIm);
    cv::Mat transformed_real = imageFourierClass::draw(W, H, FRe, true);
    cv::Mat transformed_im = imageFourierClass::draw(W, H, FIm, true);
    cv::Mat transformed_amp = imageFourierClass::draw(W, H, FAmp, true);
    display_real_im_amp(transformed_real, transformed_im, transformed_amp,
                        title + " - Transformed - (Real, Imaginary, Amplitude)");

    // Calculate and draw the inverse of FFT to get the image back
    FFTcalcul::FFT2D(W, H, FRe, FIm, fRe2, fIm2, true);
    FFTcalcul::calculateAmp(W, H, fAmp2, fRe2, fIm2);
    cv::Mat retransformed_real = imageFourierClass::draw(W, H, fRe2, false);
    cv::Mat retransformed_im = imageFourierClass::draw(W, H, fIm2, false);
    cv::Mat retransformed_amp = imageFourierClass::draw(W, H, fAmp2, false);
    display_real_im_amp(retransformed_real, retransformed_im, retransformed_amp,
                        title + " - Re-transformed - (Real, Imaginary, Amplitude)");
    delete[] fRe2; // clear memory
    delete[] fIm2;
    delete[] fAmp2;
    delete[] FRe;
    delete[] FIm;
    delete[] FAmp;

    //int k = cv::waitKey(0);

}

// Calculate and draw inverse fft with pass applied
void imageFourierClass::display_blur(cv::Mat image, double radius1, int pass, double radius2) {
    int H = image.rows, W = image.cols, c = 3;
    double *fRe = new double[H * W * c], *fIm = new double[H * W * c], *FRe = new double[H * W * c], *FIm = new double[
    H * W * c];
    double *FReBlur = new double[H * W * c], *FImBlur = new double[H * W * c], *fReBlur = new double[H * W *
                                                                                                     c], *fImBlur = new double[
    H * W * c];
    fRe = cv_to_pointer(image);
    FFTcalcul::FFT2D(W, H, fRe, fIm, FRe, FIm);
    delete[] fRe;
    delete[] fIm;
    FReBlur = FFTcalcul::blur(FRe, radius1, H, W, pass, radius2);
    delete[] FRe;
    FImBlur = FFTcalcul::blur(FIm, radius1, H, W, pass, radius2);
    delete[] FIm;
    FFTcalcul::FFT2D(W, H, FReBlur, FImBlur, fReBlur, fImBlur, true);
    delete[] fImBlur;
    cv::Mat blur_transformed_re = imageFourierClass::draw(W, H, FReBlur, true);
    delete[] FReBlur;
    cv::Mat blur_transformed_im = imageFourierClass::draw(W, H, FImBlur, true);
    delete[] FImBlur;
    cv::Mat blur_retransformed_re = imageFourierClass::draw(W, H, fReBlur, false);
    delete[] fReBlur;

    std::string title;
    if (pass<3){
        title = "Blurred with a radius divided by ";
        title.append(to_string(radius1)).append(" - (Original, Real part filtered, Transformed)");
    }else if (pass==3){
        title = "Transformed with a selected band";
        title.append(" - (Original, Real part filtered, Transformed)");
    }else{
        title = "Transformed with a band erased";
        title.append(" - (Original, Real part filtered, Transformed)");
    }
    display_real_im_amp( image,blur_transformed_re, blur_retransformed_re, title);
    blur_transformed_re.release();
    blur_transformed_im.release();
    blur_retransformed_re.release();
    image.release();
}

// interaction with the user to choose the filter
void imageFourierClass::choose_filter(cv::Mat image) {
    int filter;
    double radius_ratio=-1;
    double radius_ratio2=-1;

    while (filter < 0 || filter > 4) {
        cout
                << "Add a filter (1 : low pass filter || 2 : high pass filter || 3 : select band pass || 4 : unselect band pass || 0 to finish) \n";
        cin >> filter;
        if (filter == 0) { return ; }
    }
    while (radius_ratio<0||radius_ratio>100) {

        cout << "Radius relative to the size in % : \n";
        cin >> radius_ratio;

    }
    double radius = 100.0 / radius_ratio;
    if (filter > 2) {
        while (radius_ratio2<0||radius_ratio2>100) {
            cout << "2nd radius relative to the size in % : \n";
            cin >> radius_ratio2;

        }
        double radius2 = 100.0 / radius_ratio2;
        imageFourierClass::display_blur(image, radius, filter, radius2);
    } else {
        imageFourierClass::display_blur(image, radius, filter);
    }

}

// create a sinusoidal image to check if the fft works
cv::Mat imageFourierClass::create_sin_image(int size) {
    int n = size, m = n;
    cv::Mat sinus(n, m, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int y1 = 0; y1 < m; y1++)
        for (int x1 = 0; x1 < m; x1++) {
            cv::Vec3b color = sinus.at<cv::Vec3b>(cv::Point(x1, y1));
            color[2] = 126 + 63 * sin(M_PI * y1 / 16.0) + 63 * sin(M_PI * x1 / 16.0);
            color[1] = 126 + 63 * sin(M_PI * y1 / 16.0) + 63 * sin(M_PI * x1 / 16.0);

            sinus.at<cv::Vec3b>(cv::Point(x1, y1)) = color;
        }
    return sinus;
}
