//
// Created by leonard on 22.01.21.
//

#include "FFTcalcul.h"

void FFTcalcul::FFT(int n, bool inverse, const double *fRe, const double *fIm, double *FRe, double *FIm, int step,
                    double factor) {
    int h = log2(n);

    //Bit reversal
    FRe[(n - 1) * step] = fRe[(n - 1) * step];
    FIm[(n - 1) * step] = fIm[(n - 1) * step];
    int j = 0;
    for(int i = 0; i < n - 1; i++)
    {
        FRe[i * step] = fRe[j * step];
        FIm[i * step] = fIm[j * step];
        int k = n / 2;
        while(k <= j)
        {
            j -= k;
            k /= 2;
        }
        j += k;
    }
    // Calculate the FFT
    double ca = -1.0;
    double sa = 0.0;
    int l1 = 1, l2 = 1;
    for(int l = 0; l < h; l++)
    {
        l1 = l2;
        l2 *= 2;
        double u1 = 1.0;
        double u2 = 0.0;
        for(int j = 0; j < l1; j++)
        {
            for(int i = j; i < n; i += l2)
            {
                int i1 = i + l1;
                double t1 = u1 * FRe[i1 * step] - u2 * FIm[i1 * step];
                double t2 = u1 * FIm[i1 * step] + u2 * FRe[i1 * step];
                FRe[i1 * step] = FRe[i * step] - t1;
                FIm[i1 * step] = FIm[i * step] - t2;
                FRe[i * step] += t1;
                FIm[i * step] += t2;
            }
            double z =  u1 * ca - u2 * sa;
            u2 = u1 * sa + u2 * ca;
            u1 = z;
        }
        sa = sqrt((1.0 - ca) / 2.0);
        if(!inverse) sa =- sa;
        ca = sqrt((1.0 + ca) / 2.0);
    }
    // Divide through the factor
    for(int i = 0; i < n; i++)
    {
        FRe[i * step] /= factor;
        FIm[i * step] /= factor;
    }

}

void FFTcalcul::FFT2D(int w, int h, const double *fRe, const double *fIm, double *FRe, double *FIm, bool inverse) {
    //temporary buffers
    std::vector<double> Gr2(h * w * 3);
    std::vector<double> Gi2(h * w * 3);

    for(int y = 0; y < h; y++) // row
        for(int c = 0; c < 3; c++) // color channel
        {
            FFTcalcul::FFT(w, inverse, &fRe[y * w * 3 + c], &fIm[y * w * 3 + c], &Gr2[y * w * 3 + c], &Gi2[y * w * 3 + c], 3, 1);
        }
    for(int x = 0; x < w; x++) // column
        for(int c = 0; c < 3; c++) // color channel
        {
            FFTcalcul::FFT(h, inverse, &Gr2[x * 3 + c], &Gi2[x * 3 + c], &FRe[x * 3 + c], &FIm[x * 3 + c], w * 3, w);
        }
}

void FFTcalcul::calculateAmp(int w, int h, double *fAmp, const double *fRe, const double *fIm) {
    for(int y = 0; y < h; y++)
        for(int x = 0; x < w; x++)
            for(int c = 0; c < 3; c++)
            {
                fAmp[w * 3 * y + 3 * x + c] = sqrt(fRe[w * 3 * y + 3 * x + c] * fRe[w * 3 * y + 3 * x + c] + fIm[w * 3 * y + 3 * x + c] * fIm[w * 3 * y + 3 * x + c]);
            }
}

double *FFTcalcul::blur(double *f, double radius1, int H, int W, int pass, double radius2) {
    double *f_filter = new double[H * W * 3];
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++) {
            int x1 = x, y1 = y;
            x1 = (x + W / 2) % W;
            y1 = (y + H / 2) % H;
            for (int i = 0; i < 3; i++) {

                if (pow(x - W / 2, 2) + pow(y - H / 2, 2) < pow((double) H / 2 / radius1, 2) && pass == 1
                    // select only the interior of a radius1
                    || (pow(x - W / 2, 2) + pow(y - H / 2, 2) > pow((double) H / 2 / radius1, 2) ||
                        (pow(x - W / 2, 2) + pow(y - H / 2, 2) == 0)) && pass == 2
                    // select only the exterior of radius1 and the middle point to have a brighter image
                    || (pow(x - W / 2, 2) + pow(y - H / 2, 2) > pow((double) H / 2 / max(radius1, radius2), 2) &&
                        (pow(x - W / 2, 2) + pow(y - H / 2, 2) < pow((double) H / 2 / min(radius1, radius2), 2)) ||
                        (pow(x - W / 2, 2) + pow(y - H / 2, 2) == 0)) && pass == 3
                    // select only a band between radius1 and radius2 and also the middle point to have a brighter image
                    || (pow(x - W / 2, 2) + pow(y - H / 2, 2) > pow((double) H / 2 / min(radius1, radius2), 2) ||
                        (pow(x - W / 2, 2) + pow(y - H / 2, 2) < pow((double) H / 2 / max(radius1, radius2), 2))) &&
                       pass == 4
                    // select only the exterior of a band between radius1 and radius 2
                        ) {

                    f_filter[3 * W * y1 + 3 * x1 + i] = f[3 * W * y1 + 3 * x1 + i];
                } else {
                    f_filter[3 * W * y1 + 3 * x1 + i] = 0;
                }

            }
        }
    return f_filter;
}
